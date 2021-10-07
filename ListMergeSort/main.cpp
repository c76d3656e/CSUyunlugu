#include <stdio.h>

using namespace std;
struct ListNode{
    int val;
    ListNode *next;
    ListNode():val(),next(nullptr){}
    explicit ListNode(int x):val(x),next(nullptr){}
    ListNode(int x,ListNode* next):val(x),next(next){}
};

ListNode* InputLine(ListNode* head){
    printf("how many number in line\n");
    int n;
    scanf_s("%d",&n);
    printf("input number in order\n");
    ListNode* temphead=head;
    while(n!=0){
        int i;
        scanf_s("%d",&i);
        head->next=new ListNode(i);
        head=head->next;
        n--;
    }
    return temphead->next;
}
ListNode* spilt(ListNode* head){
    ListNode* slow=head;
    ListNode* fast=head;
    while ((fast->next!=nullptr)&&(fast->next->next!=nullptr)){
        slow=slow->next;
        fast=fast->next->next;
    }
    ListNode* mid=slow->next;
    slow->next=nullptr;
    return mid;
}

ListNode* mergeSort(ListNode* head1,ListNode* head2){
    ListNode* temphead=new ListNode();
    ListNode* cur=temphead;
    while(head1!=nullptr&&head2!=nullptr){
        if(head1->val<head2->val) {
            cur->next = head1;
            head1 = head1->next;
        }else{
            cur->next=head2;
            head2=head2->next;
        }
        cur=cur->next;
    }
    cur->next=(head1==nullptr)?head2:head1;
    return temphead->next;
}
ListNode* sortList(ListNode* head){
    if(head==nullptr||head->next==nullptr)
        return head;
    ListNode* head2=spilt(head);
    head=sortList(head);
    head2=sortList(head2);
    return mergeSort(head,head2);
}
int main(){
    ListNode* head=new ListNode();
    head=InputLine(head);
    head=sortList(head);
    while(head!=nullptr){
        printf("%d ",head->val);
        head=head->next;
    }
}
