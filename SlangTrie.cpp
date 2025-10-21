#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

int num = 0;

struct Node{
	char slang[100];
	char desc[100];
	int end;
	Node *child[26];
};

Node* createNode(char slang[], char desc[]){
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->slang, slang);
	strcpy(newNode->desc, desc);
	for(int i = 0; i<26; i++){
		newNode->child[i]=0;
	}
	newNode->end = 0;
	return newNode;
}

Node *root = createNode("", "");

void insertNode(char slang[], char desc[]){
	Node *curNode = root;
	
	for(int i = 0; i<strlen(slang); i++){
		int index=slang[i]-'a';
		if(!curNode->child[index]){
			curNode->child[index]=createNode("", "");
		}
		curNode = curNode->child[index];		
	}
	curNode->end = 1;
	
	if(strcmp(curNode->slang, "")==0) puts("Successfully Released new slang word");
	else puts("Successfully Updated new slang word");
	
	strcpy(curNode->slang, slang);
	strcpy(curNode->desc, desc);
	puts("Press enter to continue...");
	getch();
}
		
void printAll(Node *start){
	if(start){
		if(start->end==1){
			num++;
			printf("%d. %s\n", num, start->slang);
		}
		for(int i = 0; i<26; i++){
			printAll(start->child[i]);
		}
	}
}

Node* searchNode(char slang[]){
	Node *curNode = root;
	for(int i = 0; i<strlen(slang); i++){
		int index=slang[i]-'a';
		if(!curNode->child[index]){
			return NULL;
		}
		curNode = curNode->child[index];		
	}
	if(strcmp(curNode->slang, "") == 0){
		return NULL;
	}
	return curNode;
}

void printPrefix(char slang[]){
	Node *curNode = root;
	for(int i = 0; i<strlen(slang); i++){
		int index=slang[i]-'a';
		if(curNode->child[index]==NULL){
			printf("\033[0;31mThere is no prefix \"%s\" in the dictionary.\033[0m\n", slang);
			return;
		}
		curNode = curNode->child[index];	
	}
	printAll(curNode); 	
}


int main(){
	int number;
	char slang[100];
	char desc[100];
	char search[100];
	
	while(true){
		system("cls");
		puts("1. Release a new Slang word");
		puts("2. Search a slang word");
		puts("3. View all slang word starting with a certain prefix word");
		puts("4. View all slang words");
		puts("5. Exit");
		do{
			printf(">>> ");
			scanf("%d", &number);
			if(number==5){
				puts("Thank you... Have a nice day :)");
				exit(0);
			}
		}while(number<0||number>5);
		
		switch(number){
			case 1:{
				while(1){
					printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
					scanf(" %[^\n]", slang);
					int count = 0;
					for(int i = 0; i<strlen(slang); i++){
						if(slang[i]==' '){
							count += 0;
						}else{
							count += 1;
						}
					}
					if(count==strlen(slang) && strlen(slang)>=2) break;
				}
				while(1){
					printf("Input a new slang word description [Must be more than 2 words]: ");
					scanf(" %[^\n]", desc);
					int count = 0;
					for(int i = 0; i<strlen(desc); i++){
						if(desc[i]==' '){
							count += 1;
						}
					}
					if(count>=2) break;
				}
				insertNode(slang, desc);
				break;
			}
			case 2:{
				while(1){
					printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
					scanf(" %[^\n]", search);
					int count = 0;
					for(int i = 0; i<strlen(search); i++){
						if(search[i]==' '){
							count += 0;
						}else{
							count += 1;
						}
					}
					if(count==strlen(search) && strlen(search)>=2) break;
				}
				Node *temp = searchNode(search);
				if(temp){
					puts("\033[0;32mFOUND!!!\033[0m");
					printf("Slang word\t: %s\n", temp->slang);	
					printf("Description\t: %s\n", temp->desc);	
				}else{
					printf("\033[0;31mThere is no word \"%s\" in the dictionary.\033[0m\n", search);
				}
				puts("Press enter to continue...");
				getch();
				break;
			}
			case 3:{
				num = 0;
				while(1){
					printf("Input a prefix to be searched: ");
					scanf(" %[^\n]", search);
					int count = 0;
					for(int i = 0; i<strlen(search); i++){
						if(search[i]==' '){
							count += 0;
						}else{
							count += 1;
						}
					}
					if(count==strlen(search) && strlen(search)>=2) break;
				}
				printPrefix(search); 
				puts("Press enter to continue...");
				getch();
				break;
			}
			case 4:{
				num = 0;
				printAll(root); 
				puts("Press enter to continue...");
				getch();
				break;
			}
		}
	}
	
	return 0;
}
