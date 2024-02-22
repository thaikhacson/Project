# Project: Resident Information Management

## Objective
Develop a C program to manage resident information in an apartment complex, including basic functions such as adding, deleting, editing, and searching resident information. This program aims to efficiently and accurately manage residents, ensuring data is updated and accessible quickly.

## Data Structure
### Member
- **Description**: Structure to store basic information of a resident.
- **Field Information**: RFID UID, room number, name, license plate.

Example Code:

```
typedef struct {
    char uid[20];        // RFID UID
    char roomNumber[10]; // Room Number
    char name[50];       // Name
    char licensePlate[20]; // License Plate
} Member;
```

### MemberNode
- **Description**: Node in a linked list containing Member information.
- **Field Information**: Member data, pointer to the next MemberNode.

**Example Code:**

```
typedef struct MemberNode {
    Member data;
    struct MemberNode* next;
} MemberNode;

MemberNode* createMemberNode(Member member) {
    MemberNode* newNode = (MemberNode*)malloc(sizeof(MemberNode));
    newNode->data = member;
    newNode->next = NULL;
    return newNode;
}

```

## Main Functions
### Add Member
- **Description**: Write new member information to the end of a CSV file.
- **Input**: New Member information.
- **Output**: Updated CSV file.

Example Code:

```
void addMember(const char* filename, Member member);
```

### Delete Member
- **Description**: Delete member information based on UID from a CSV file.
- **Input**: UID of the member to be deleted.
- **Output**: Updated CSV file.

Example Code:

```
void deleteMember(const char* filename, const char* uid);
```

### Edit Member
- **Description**: Update member information based on UID in a CSV file.
- **Input**: Updated Member information and UID.
- **Output**: Updated CSV file.

Example Code:

```
void editMember(const char* filename, Member updatedMember);
```

### Search Member
- **Description**: Search for member information based on UID or license plate.
- **Input**: Search value and criteria (UID/License plate).
- **Output**: Display found information or indicate not found.

Example Code:

```
int searchByUID(const Member* member, const char* uid);
int searchByLicensePlate(const Member* member, const char* licensePlate);
Member searchMember(const char* filename, const char* searchValue, SearchFunction searchFunc);
```

## Additional Details

- **CSV File Format**: Ensure adherence to the specified CSV format with columns for RFID UID, Room Number, Name, and License Plate.
- **RFID UID**: Unique character string for each resident's identification.
- **Room Number**: Room code for each resident.
- **Name**: Full name of the resident.
- **License Plate:**: Resident's vehicle license plate (if applicable).

Example Code:

```
uID,roomNumber,name,licensePlates
123456789,A-101,Nguyen Van A,51F-123.45
```
