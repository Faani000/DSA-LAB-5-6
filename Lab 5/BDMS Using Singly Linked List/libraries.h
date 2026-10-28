#include "libraries.h"

DonorNode* CreateDonor(int id, string name, string group, string phone) {
    DonorNode* donor = new DonorNode;
    donor->donorID = id;
    donor->name = name;
    donor->bloodGroup = group;
    donor->phone = phone;
    donor->next = nullptr;
    return donor;
}
