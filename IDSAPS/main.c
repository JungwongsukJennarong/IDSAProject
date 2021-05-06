// Name :
// Student ID :

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const char* word, const char* query_word, const long long pos,FILE* output_file, const int* flag){	
		char spos[100];			
		if (strcmp(word,query_word) == 0){
			itoa(pos, spos, 10);
			if (*flag == 2){						
				fprintf(output_file,", %s",spos);	
			} else {
				printf("%d",*flag);		
				fprintf(output_file,"%s",spos);
			} 
				
			return 1;
		}
		return 0;
}

// Only ONE Word 
int seq_search(FILE* data_file, const char* word_to_find, FILE* output_file){
	int num_of_word;
	int word_length;
	char ch;
	char word[1000];	
	int flag = 1;
	int result = 0;
	do {		
	//	space = 0;				
		word_length = 0;
	    while((ch = fgetc(data_file)) != ' ' &&  ch != '\n' && ch != EOF && ch != '\t' ){	    		
			word[word_length] = ch;    	    	
			++word_length;
				 	    	
		}	
		if (word_length){
			word[word_length] = '\0';
			++word_length;
			++num_of_word; 
			result += compare(word,word_to_find,num_of_word,output_file,&flag);
			flag = 2;
		}		
	} while(ch != EOF );
	return result;
}

// 2 WORDS ABOVE
int seq_multi_search(FILE* data_file, const char* word_to_find, FILE* output_file, const int space_req){
	long long num_of_word = 0;
	int word_length;
	char ch;
	char word[1000];	
	char* prev_word[100];
	int word_in_line = 0;
	long result = 0;
	int starting_pos = 0;
	int t = 0;
	int flag = 1;
	
	do {	
//	printf("D\n");	
		word_length = 0;
	    while((ch = fgetc(data_file)) != ' ' && ch  != '\n' && ch != EOF && ch != '\t' ){	  
			word[word_length] = ch;    	    	
			++word_length;	    	
		//	printf("%c",ch);
		}	
	//	printf("\n");
		if (word_length){
			word[word_length] = '\0';
			prev_word[word_in_line] = malloc(50);
			strcpy(prev_word[word_in_line], word);		
			++word_in_line;
			word_in_line = (100+word_in_line)%100;
			if (num_of_word > space_req){
			//	printf("Larger!\n");
				char* string;
				int i = 0;
				string = malloc(500);
				starting_pos = (100+word_in_line-space_req-1)%100;
			//	printf("%d",starting_pos);
				strcpy(string, prev_word[starting_pos]);
				for (i = 1; i <= space_req; i++){
					strcat(string, " ");
					strcat(string, prev_word[(starting_pos+i)%100]);									
				}
				result += compare(string,word_to_find,num_of_word+1-space_req,output_file,&flag);		
				flag = 2;
			}
			++num_of_word; 		
						
		}	
	} while(ch != EOF );
	return result;
}


int main(int argc, char *argv[]) { 
	FILE *data_file;
	FILE *query_file;
	FILE *output_file;
	int i;
	// Check the number of Arguments
    if(argc!=3){
    	printf("\nInvalid Arguments!  "); 
        return 0;
	}       
      
    // Query File
    query_file = fopen(argv[2], "r");     
    // Output File
    output_file = fopen("output.txt","w");
	fprintf(output_file,"Search result are as follow.");
	// Temp Character Pointer pointing to a single word
	char word[1000];
	long word_length = 0;
	long long num_of_word = 0;
	char ch;
	
	// Read Query
	do {		
		word_length = 0;
		int space = 0;
	    while((ch = fgetc(query_file)) != '\n' && ch != EOF){
	    	word[word_length] = ch;    	
	    	++word_length;    	
	    	if (ch == ' '){
	    		++space;
			}
		}
		if (word_length){
			word[word_length] = '\0';
			++word_length;
			i++;
			printf("Searching query no.%d \"%s\" with space %d\n",i,word,space);
			data_file = fopen(argv[1], "r");   
			fprintf(output_file,"\nFor qurty no.%d \"%s\"",i,word);
			if (!space){
				printf("Result : %d\n\n",seq_search(data_file,word,output_file));
			} else {
				printf("Result : %d\n\n",seq_multi_search(data_file,word,output_file,space));
			}
					
			fprintf(output_file,"\n");	
			fclose(data_file);		
		}		
	} while(ch != EOF );	
			
    fclose(output_file);    
    fclose(query_file);
    printf("Done >3<"); 
    return 0; 
}
