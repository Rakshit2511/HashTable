#include<stdio.h>
struct node
{
    char ch[100];
    int count;
    struct node *next;
};
struct hashtable
{
    struct node *head;
    struct node *tail;
    int count;
};
void makehashtable(struct hashtable *h,char *c)
{
    char ch[100];
    int i=0,j=0,flag=0,key;
    while(c[i]!='\0')
    {
        if(c[i]==' ')
        {
            flag=0;
        }
        else
        {
            if(flag!=1)
            {
                j=0;
                while(c[i+1]!=' '&c[i+1]!='\0')
                {
                    ch[j]=c[i];
                    i++;
                    j++;
                }
                ch[j]=c[i];
                j++;
                ch[j]='\0';
                key=generatekey(ch);
                insertionfromtail(&h[key].head,ch);
            }
        }
        i++;
    }
}
int generatekey(char *c)
{
    int i,sum,key;
    sum=c[0];
    i=1;
    while(c[i]!='\0')
    {
        sum=sum+c[i];
        i++;
    }
    key=sum%100;
    return key;
}
void insertionfromtail(struct node **start,char *c)
{
    struct node *nextnode=(struct node *)malloc(sizeof(struct node));
    strcpy(nextnode->ch,c);
    nextnode->next=NULL;
    nextnode->count=1;
    if(*start==NULL)
    {
        *start=nextnode;
    }
    else
    {
        struct node *temp,*temp1;
        temp=*start;
        int check=0;
        while(temp!=NULL)
        {
            if(strcmp(nextnode->ch,temp->ch)==0)
            {
                temp->count=(temp->count)+1;
                check=1;
            }
            temp1=temp;
            temp=temp->next;
        }
        if(check==0)
            temp1->next=nextnode;
        else
            free(nextnode);
    }
}
void displayindexdata(struct node **start)
{
    struct node *temp;
    temp=*start;
    while(temp!=NULL)
    {
        printf("%s %d ",temp->ch,temp->count);
        temp=temp->next;
    }
}
void searchindex(struct hashtable *h,char *c)
{
    int key;
    key=generatekey(c);
    searchword(&h[key],c);
}
void searchword(struct hashtable *h,char *c)
{
    struct node *temp;
    temp=h->head;
    while(temp!=NULL)
    {
        if(strcmp(c,temp->ch)==0)
        {
            printf("\nFound '%s' %d times\n",temp->ch,temp->count);
            break;
        }
        temp=temp->next;
    }
}
void displayhashtable(struct hashtable *h,int s)
{
    int i;
    for(i=0;i<100;i++)
    {
        printf("%d ",i);
        displayindexdata(&(h[i].head));
        printf("\n");
    }
}
int main()
{
    int i,s=100;
    struct hashtable h[s];
    char c[1000];
    for(i=0;i<s;i++)
        h[i].head=NULL;
    FILE *fp;
    fp=fopen("file.txt","r");
    while((fscanf(fp,"%s",&c))!=EOF)
    {
        makehashtable(&h,&c);
    }
    displayhashtable(&h,s);
    printf("\nENTER THE WORD TO SEARCH\n");
    gets(c);
    searchindex(&h,&c);
}
