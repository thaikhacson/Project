#include "RFID.h"
#include "SPI.h"

void RFID(int chipSelectPin, int NRSTPD) {
	_chipSelectPin = chipSelectPin;
  _NRSTPD = NRSTPD;

	//  pinMode(_chipSelectPin,OUTPUT);
	//  digitalWrite(_chipSelectPin, LOW);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = chipSelectPin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOA, chipSelectPin);
	
//  pinMode(_NRSTPD,OUTPUT);
//  digitalWrite(_NRSTPD, HIGH);
	GPIO_InitStruct.GPIO_Pin = NRSTPD;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_SetBits(GPIOA, NRSTPD);
}

bool RFID_isCard() {
  unsigned char status;
  unsigned char str[MAX_LEN];

  status = MFRC522Request(PICC_REQIDL, str);
  if (status == MI_OK)
    return true;
  else
    return false;
}

bool RFID_readCardSerial() {

  unsigned char status;
  unsigned char str[MAX_LEN];
  
  status = anticoll(str);
  memcpy(serNum, str, 5);
  
  if (status == MI_OK)
    return true;
  else
    return false;
}

void init() {
  //digitalWrite(_NRSTPD,HIGH);
	GPIO_SetBits(GPIOA, _NRSTPD);

  reset();

  //Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
  writeMFRC522(TModeReg, 0x8D);   //Tauto=1; f(Timer) = 6.78MHz/TPreScaler
  writeMFRC522(TPrescalerReg, 0x3E);  //TModeReg[3..0] + TPrescalerReg
  writeMFRC522(TReloadRegL, 30);
  writeMFRC522(TReloadRegH, 0);
  writeMFRC522(TxAutoReg, 0x40);    //100%ASK
  writeMFRC522(ModeReg, 0x3D);    // CRC valor inicial de 0x6363

  //ClearBitMask(Status2Reg, 0x08); //MFCrypto1On=0
  //writeMFRC522(RxSelReg, 0x86);   //RxWait = RxSelReg[5..0]
  //writeMFRC522(RFCfgReg, 0x7F);     //RxGain = 48dB

  antennaOn();    
}

void RFID_reset(void) {
  writeMFRC522(CommandReg, PCD_RESETPHASE);
}

void RFID_setBitMask(unsigned char reg, unsigned char mask) {
  unsigned char tmp;
  tmp = readMFRC522(reg);
  writeMFRC522(reg, tmp | mask);  // set bit mask
}

void RFID_clearBitMask(unsigned char reg, unsigned char mask) {
  unsigned char tmp;
  tmp = readMFRC522(reg);
  writeMFRC522(reg, tmp & (~mask));  // clear bit mask
}

void RFID_antennaOn(void) {
  unsigned char temp;

  temp = readMFRC522(TxControlReg);
  if (!(temp & 0x03))
  {
    setBitMask(TxControlReg, 0x03);
  }
}

void RFID_antennaOff(void) {
  unsigned char temp;

  temp = readMFRC522(TxControlReg);
  if (!(temp & 0x03))
  {
    clearBitMask(TxControlReg, 0x03);
  }
}

void RFID_calculateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData) {
  unsigned char i, n;

  clearBitMask(DivIrqReg, 0x04);
  setBitMask(FIFOLevelReg, 0x80);
  //Write_MFRC522(CommandReg, PCD_IDLE);

  for (i=0; i<len; i++)
  writeMFRC522(FIFODataReg, *(pIndata+i));
  writeMFRC522(CommandReg, PCD_CALCCRC);

  i = 0xFF;
  do
  {
    n = readMFRC522(DivIrqReg);
    i--;
  }
  while ((i!=0) && !(n&0x04));      //CRCIrq = 1

  pOutData[0] = readMFRC522(CRCResultRegL);
  pOutData[1] = readMFRC522(CRCResultRegM);
}

void RFID_writeMFRC522(unsigned char addr, unsigned char val) {
  //digitalWrite(_chipSelectPin, LOW);
	GPIO_ResetBits(GPIOA, _chipSelectPin);

  //SPI.transfer((addr<<1)&0x7E);
  //SPI.transfer(val);
	SPI_Tranfer(SPI1, SPI1_GPIO, SPI1_NSS, (addr<<1)&0x7E);
	SPI_Tranfer(SPI1, SPI1_GPIO, SPI1_NSS, val);

  //digitalWrite(_chipSelectPin, HIGH);
	GPIO_SetBits(GPIOA, _chipSelectPin);
}

unsigned char RFID_readMFRC522(unsigned char addr) {
  unsigned char val;
  //digitalWrite(_chipSelectPin, LOW);
  //SPI.transfer(((addr<<1)&0x7E) | 0x80);
  //val = SPI.transfer(0x00);
  //digitalWrite(_chipSelectPin, HIGH);
	GPIO_ResetBits(GPIOA, _chipSelectPin);
	SPI_Tranfer(SPI1, SPI1_GPIO, SPI1_NSS, ((addr<<1)&0x7E) | 0x80);
	val = SPI_Tranfer(SPI1, SPI1_GPIO, SPI1_NSS, 0x00);
	GPIO_SetBits(GPIOA, _chipSelectPin);
  return val;
}

unsigned char RFID_MFRC522Request(unsigned char reqMode, unsigned char *TagType) {
  unsigned char status;
  unsigned int backBits;

  writeMFRC522(BitFramingReg, 0x07);    //TxLastBists = BitFramingReg[2..0] ???

  TagType[0] = reqMode;
  status = MFRC522ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

  if ((status != MI_OK) || (backBits != 0x10))
    status = MI_ERR;

  return status;
}

unsigned char RFID_MFRC522ToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen, unsigned char *backData, unsigned int *backLen) {
  unsigned char status = MI_ERR;
  unsigned char irqEn = 0x00;
  unsigned char waitIRq = 0x00;
  unsigned char lastBits;
  unsigned char n;
  unsigned int i;

  switch (command)
  {
    case PCD_AUTHENT:
    {
      irqEn = 0x12;
      waitIRq = 0x10;
      break;
    }
    case PCD_TRANSCEIVE:
    {
      irqEn = 0x77;
      waitIRq = 0x30;
      break;
    }
    default:
      break;
  }

  writeMFRC522(CommIEnReg, irqEn|0x80);
  clearBitMask(CommIrqReg, 0x80); 
  setBitMask(FIFOLevelReg, 0x80);       //FlushBuffer=1, FIFO???

  writeMFRC522(CommandReg, PCD_IDLE);

  for (i=0; i<sendLen; i++)
    writeMFRC522(FIFODataReg, sendData[i]);

  writeMFRC522(CommandReg, command);
  if (command == PCD_TRANSCEIVE)
    setBitMask(BitFramingReg, 0x80);    //StartSend=1,transmission of data starts

  i = 2000;
  do
  {
    //CommIrqReg[7..0]
    //Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
    n = readMFRC522(CommIrqReg);
    i--;
  }
  while ((i!=0) && !(n&0x01) && !(n&waitIRq));

  clearBitMask(BitFramingReg, 0x80);      //StartSend=0

  if (i != 0)
  {
    if(!(readMFRC522(ErrorReg) & 0x1B)) //BufferOvfl Collerr CRCErr ProtecolErr
    {
      status = MI_OK;
      if (n & irqEn & 0x01)
        status = MI_NOTAGERR;

      if (command == PCD_TRANSCEIVE)
      {
        n = readMFRC522(FIFOLevelReg);
        lastBits = readMFRC522(ControlReg) & 0x07;
        if (lastBits)
          *backLen = (n-1)*8 + lastBits;
        else
          *backLen = n*8;

        if (n == 0)
          n = 1;
        if (n > MAX_LEN)
          n = MAX_LEN;

        for (i=0; i<n; i++)
          backData[i] = readMFRC522(FIFODataReg);
      }
    }
    else
      status = MI_ERR;
  }

  //SetBitMask(ControlReg,0x80);           //timer stops
  //Write_MFRC522(CommandReg, PCD_IDLE);

  return status;
}

unsigned char RFID_anticoll(unsigned char *serNum) {
  unsigned char status;
  unsigned char i;
  unsigned char serNumCheck=0;
  unsigned int unLen;

  //ClearBitMask(Status2Reg, 0x08);   //TempSensclear
  //ClearBitMask(CollReg,0x80);     //ValuesAfterColl
  writeMFRC522(BitFramingReg, 0x00);    //TxLastBists = BitFramingReg[2..0]

  serNum[0] = PICC_ANTICOLL;
  serNum[1] = 0x20;
  status = MFRC522ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

  if (status == MI_OK)
  {
    //??????
    for (i=0; i<4; i++)
      serNumCheck ^= serNum[i];
    if (serNumCheck != serNum[i])
      status = MI_ERR;
  }

  //SetBitMask(CollReg, 0x80);    //ValuesAfterColl=1

  return status;
}

unsigned char RFID_auth(unsigned char authMode, unsigned char BlockAddr, unsigned char *Sectorkey, unsigned char *serNum) {
  unsigned char status;
  unsigned int recvBits;
  unsigned char i;
  unsigned char buff[12];

  buff[0] = authMode;
  buff[1] = BlockAddr;
  for (i=0; i<6; i++)
    buff[i+2] = *(Sectorkey+i);
  for (i=0; i<4; i++)
    buff[i+8] = *(serNum+i);
    
  status = MFRC522ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);
  if ((status != MI_OK) || (!(readMFRC522(Status2Reg) & 0x08)))
    status = MI_ERR;

  return status;
}


unsigned char RFID_read(unsigned char blockAddr, unsigned char *recvData) {
  unsigned char status;
  unsigned int unLen;

  recvData[0] = PICC_READ;
  recvData[1] = blockAddr;
  calculateCRC(recvData,2, &recvData[2]);
  status = MFRC522ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

  if ((status != MI_OK) || (unLen != 0x90))
    status = MI_ERR;

  return status;
}

unsigned char RFID_write(unsigned char blockAddr, unsigned char *writeData) {
  unsigned char status;
  unsigned int recvBits;
  unsigned char i;
  unsigned char buff[18];

  buff[0] = PICC_WRITE;
  buff[1] = blockAddr;
  calculateCRC(buff, 2, &buff[2]);
  status = MFRC522ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

  if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    status = MI_ERR;

  if (status == MI_OK)
  {
    for (i=0; i<16; i++)
      buff[i] = *(writeData+i);
      
    calculateCRC(buff, 16, &buff[16]);
    status = MFRC522ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);

    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
      status = MI_ERR;
  }

  return status;
}

unsigned char RFID_selectTag(unsigned char *serNum) {
  unsigned char i;
  unsigned char status;
  unsigned char size;
  unsigned int recvBits;
  unsigned char buffer[9];

  //ClearBitMask(Status2Reg, 0x08);                        //MFCrypto1On=0

  buffer[0] = PICC_SElECTTAG;
  buffer[1] = 0x70;

  for (i=0; i<5; i++)
    buffer[i+2] = *(serNum+i);

  calculateCRC(buffer, 7, &buffer[7]);
  
  status = MFRC522ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
  if ((status == MI_OK) && (recvBits == 0x18))
    size = buffer[0];
  else
    size = 0;
  return size;
}

void RFID_halt(void) {
  unsigned char status;
  unsigned int unLen;
  unsigned char buff[4];

  buff[0] = PICC_HALT;
  buff[1] = 0;
  calculateCRC(buff, 2, &buff[2]);

  status = MFRC522ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
}