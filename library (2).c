#include<stdio.h>
#include<stdlib.h>
struct BigInteger
{
    int data;
    struct BigInteger *next;
};

int length(struct BigInteger *head)
{
    int l=0;
    while(head)
    {
        head=head->next;
        l++;
    }
    return l;
}
int compare(struct BigInteger *head1, struct BigInteger *head2)
{
    while(head1 && head2)
    {
        if(head1->data>head2->data)
            return 1;
        if(head1->data<head2->data)
            return -1;
        head1=head1->next;
        head2=head2->next;
    }
    return 0;
}
int greater(struct BigInteger*head1,struct BigInteger* head2)
{
    if(length(head1)>length(head2))
      {
          return 1;
      }
      else if(length(head1)<length(head2))
      {
          return -1;
      }
      else
      {
          if(compare(head1,head2)==1)
          {
              return 1;
          }
          else if(compare(head1,head2)==-1)
          {
              return -1;
          }
          else
          {
            return 0;
          }
      }
}
void Head(struct BigInteger **head,int val)//adding at the head
{
  struct BigInteger* temp=(struct BigInteger*)malloc(sizeof(struct BigInteger));
  if(temp==NULL)
  {
    printf("Memory Allocation Failed!!\n");
    return;
  }
  temp->data=val;
  if((*head)==NULL)
  {
    (*head)=temp;
    temp->next=NULL;
    return;
  }
  temp->next=(*head);
  (*head)=temp;
}
void Tail(struct BigInteger **head,int val)//adding at the tail
{
  struct BigInteger* temp=(struct BigInteger*)malloc(sizeof(struct BigInteger));
  if(temp==NULL)
  {
    printf("Memory Allocation Failed!!\n");
    return;
  }
  temp->data=val;
  temp->next=NULL;
  if((*head)==NULL)
  {
    (*head)=temp;
    return;
  }
  struct BigInteger *itr=(*head);
  while(itr->next!=NULL)
    {
      itr=itr->next;
    }
  itr->next=temp;
}
struct BigInteger *initialize(char a[])
{
    struct BigInteger *head=NULL;
  int i=0;
  int v=0;
  while(a[i]!='\0')
  {
    v=(int)a[i]-48;
    Tail(&head,v);
    i++;
  }
  return head;
}
void deletefromtail(struct BigInteger **head)
{
    struct BigInteger *temp=NULL;
    if(!(*head))                                               //no BigInteger present
    {
    return;
    }
    if(!(*head)->next)                                         //one BigInteger present
    {
        temp=*head;
        *head=NULL;
        free(temp);
        return;
    }
    struct BigInteger *itr=*head;
    while(itr->next->next!=NULL)
    {
        itr=itr->next;
    }
    temp=itr->next;
    itr->next=NULL;
    free(temp);
}
void deletefromhead(struct BigInteger **head)
{
    struct BigInteger *temp=(*head);
    if(!(*head))
        return;
    (*head)=(*head)->next;
    free(temp);
}
void DisplayLL(struct BigInteger *head)//displaying as a linked list
{
  while(head!=NULL)
    {
      printf("%d->",head->data);
      head=head->next;
    }
  printf("NULL\n");
}
void display(struct BigInteger *head)//displaying as a number
{
  if(head==NULL)
  {
    return;
  }
  printf("%d",head->data);
  display(head->next);
}
void reverseLL(struct BigInteger **head)//reversing the linked list
{
  struct BigInteger *current=NULL;
  struct BigInteger *next= (*head)->next;
  (*head)->next=NULL;

  while(next!=NULL)
    {
      current=next;
      next=next->next;
      current->next=(*head);
      (*head)=current;
    }
}
struct BigInteger *add(struct BigInteger *head1, struct BigInteger *head2) {
  if(head1==NULL)
    return head2;
  else if(head2==NULL)
    return head1;
  reverseLL(&head1);
  reverseLL(&head2);
  struct BigInteger *h1 = head1;
  struct BigInteger *h2 = head2;
  struct BigInteger *add = NULL;
  int sum = 0;
  int carry = 0;
  while (head1 || head2) {
    sum = 0;
    if (head1)
      sum += head1->data;
    if (head2)
      sum += head2->data;
    sum += carry;
    carry = sum / 10;
    sum = sum % 10;
    Head(&add, sum);
    if (head1)
      head1 = head1->next;
    if (head2)
      head2 = head2->next;
  }
  if (carry)
    Head(&add, carry);
  reverseLL(&h1);
  reverseLL(&h2);
  return add;
}
struct BigInteger* Subtraction(struct BigInteger *head1,struct BigInteger *head2)//we are assuming that first number is always bigger than second one
{
  reverseLL(&head1);
  reverseLL(&head2);
  struct BigInteger *h1 = head1;
  struct BigInteger *h2 = head2;
  struct BigInteger *subtract=NULL;
  int diff=0;
  int borrow=0;
  while(head1||head2)
    {
      diff=0;
      if(head1)
        diff+=head1->data;
      if(head2)
        diff-=head2->data;
      diff-=borrow;
      if(diff<0)
      {
        diff+=10;
        borrow=1;
      }
      Head(&subtract,diff );
      if(head1)
        head1=head1->next;
      if(head2)
        head2=head2->next;
    }
    reverseLL(&h1);
  reverseLL(&h2);
  return subtract;
}
struct BigInteger* sub(struct BigInteger *head1,struct BigInteger *head2)
{
    struct BigInteger *subtract;
    if(length(head1)>length(head2))
            {
                subtract = Subtraction(head1, head2);
            }
            else if(length(head1)<length(head2))
            {
                subtract = Subtraction(head2, head1);
                subtract->data=-subtract->data;
            }
            else
            {
                if(compare(head1,head2)==1)
                {
                    subtract = Subtraction(head1, head2);
                }
                else if(compare(head1,head2)==-1)
                {
                    subtract = Subtraction(head2, head1);
                    subtract->data=-subtract->data;
                }
                else
                {
                    subtract = (struct BigInteger*)malloc(sizeof(struct BigInteger));
                    subtract->data=0;
                    subtract->next=NULL;
                }
            }
            return subtract;
}
struct BigInteger* mul(struct BigInteger *head1, struct BigInteger *head2)
{
  reverseLL(&head1);
  reverseLL(&head2);
  struct BigInteger *h1=head1;
  struct BigInteger *h2=head2;
  struct BigInteger *itr=head1;
  struct BigInteger *add1=NULL;
  struct BigInteger *add2=(struct BigInteger*)malloc(sizeof(struct BigInteger));
  add2->data=0;
  add2->next=NULL;
  struct BigInteger *add3=NULL;
  int i=0;
  int sum=0;
  int carry=0;
  while(head2)
    {
      while(itr)
      {
        sum=0;
        sum+=itr->data;
        sum*=head2->data;
        sum+=carry;
        carry=sum/10;
        sum=sum%10;

        Head(&add1,sum);
        itr=itr->next;
      }
      if(carry)
      Head(&add1,carry);
      int n=i;

      while(n--)
        {
          Tail(&add1,0);
        }
      add2=add(add1,add2);
      add1=NULL;
      itr=head1;
      head2=head2->next;
      i++;
    }
    reverseLL(&h1);
    reverseLL(&h2);
  return add2;
}
struct BigInteger* div1(struct BigInteger *head1 ,struct BigInteger *head2)
{
    if(greater(head1,head2)==-1)
    {
        struct BigInteger *div=(struct BigInteger*)malloc(sizeof(struct BigInteger));
        div->data=0;
        div->next=NULL;
        return div;
    }
    int i=length(head1)-length(head2);
                        //printf("difference between numbers length:%d\n",i);
    struct BigInteger *div=NULL;
    int count=0;
    if(compare(head1,head2)==-1)
        i-=1;
                      // printf("difference after compare:%d\n",i);
    for(int k=0;k<i;k++)
    {
        Tail(&head2,0);
    }
                      //  printf("after adding zeros:");
                      //DisplayLL(head2);
    while(i>-1)
    {
        i--;
        while(greater(head1,head2)==1 || greater(head1,head2)==0)
        {
            head1=Subtraction(head1,head2);

        if(head1->data==0)
            {
                deletefromhead(&head1);
            }
            count++;
                        //printf("after deleting zero:");
                        //DisplayLL(head1);
        }

                        //printf("%d\n",count%10);
                        int c=count%10;
        Tail(&div,c);
        deletefromtail(&head2);
                        //printf("after delete from tail:");
                        //DisplayLL(head2);
        count=0;
    }
    return div;
}