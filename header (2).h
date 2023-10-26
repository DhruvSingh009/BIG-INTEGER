int length(struct BigInteger *head);

int compare(struct BigInteger *head1, struct BigInteger *head2);

int greater(struct BigInteger*head1,struct BigInteger* head2);

void Head(struct BigInteger **head,int val);

void Tail(struct BigInteger **head,int val);

struct BigInteger *initialize(char a[]);

void deletefromtail(struct BigInteger **head);

void deletefromhead(struct BigInteger **head);

void DisplayLL(struct BigInteger *head);

void display(struct BigInteger *head);

void reverseLL(struct BigInteger **head);

struct BigInteger *add(struct BigInteger *head1, struct BigInteger *head2);

struct BigInteger* Subtraction(struct BigInteger *head1,struct BigInteger *head2);

struct BigInteger* sub(struct BigInteger *head1,struct BigInteger *head2);

struct BigInteger* mul(struct BigInteger *head1, struct BigInteger *head2);

struct BigInteger* div1(struct BigInteger *head1 ,struct BigInteger *head2);

