#ifndef MANAGER_H
#define MANAGER_H
#include "member.h"

void addMember(const char* filename, Member member);
void deleteMember(const char* filename, const char* uid);
void editMember(const char* filename, Member updatedMember, const char* uid);
// int searchByUID(const Member* member, const char* uid);
// int searchByLicensePlate(const Member* member, const char* licensePlate);
// Member searchMember(const char* filename, const char* searchValue, int (*searchFunc)(const Member*, const char*));

#endif
