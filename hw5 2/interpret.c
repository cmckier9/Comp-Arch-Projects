#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void scan(short*y);

int main(int argc, char* argv[]){
	//Initialize the 4 registers
	short ax = 0;
	short bx = 0;
	short cx = 0;
	short dx = 0;
	
	//Scan the file and create an array of strings that are the lines of the file
	FILE* fp = fopen(argv[1], "r");
	int length = 0;
	for (char i = fgetc(fp); i != EOF; i = getc(fp)) {
    		if (i == '\n') length++;
	}
	fclose(fp);
	
	char lineArr[length][30];
	FILE* gp = fopen(argv[1], "r");
	for (int i = 0; i < length; i++){
		fgets(lineArr[i], 30, gp);
	}
	fclose(gp);
	//for (int i = 0; i < length; i++){
	//	printf("%s\n", lineArr[i]);
	//}
	//Execute commands
	int i = 0;
	while(i < length){
		//Tokenize line and check if its empty
		char line[30];
		strcpy(line, lineArr[i]);
		char *token = strtok(line, " ");
		
		//Read
		if (strcmp(token, "read") == 0){
			token = strtok(NULL, " ");
			//printf("ins: read, dest = %s\n", token);
			if (strcmp(token, "ax\n") == 0) {scan(&ax);}
			else if (strcmp(token, "bx\n") == 0) {scan(&bx);}
			else if (strcmp(token, "cx\n") == 0) {scan(&cx);}
			else {scan(&dx);}
			//printf("ins: read, i = %d, ax = %hi, bx = %hi\n", i, ax,  bx);
		
		//Jump
		} else if (strcmp(token, "jmp") == 0) {
			token = strtok(NULL, " ");
			int jmpNum = atoi(token);
			i = jmpNum;
			continue;

		//Jump less than or equal to
		} else if ( strcmp(token, "jle") == 0) {
			token = strtok(NULL, " ");
			int jmpLine = atoi(token);
			token = strtok(NULL, " ");

			//Check if first number is register ax
			if (strcmp(token, "ax") == 0) {
				token = strtok(NULL, " ");
				if (strcmp(token, "ax\n") == 0){
					if (ax <= ax){	
						i = jmpLine;
						continue;
					}
				}else if (strcmp(token, "bx\n") == 0 ) {
					if (ax <= bx){ 
						i = jmpLine;
						continue;
					}
				} else if (strcmp(token, "cx\n") == 0){
					if (ax <= cx){ 
						i = jmpLine;
						continue;
					}
				} else if (strcmp(token, "dx\n") == 0) { 
					if(ax <= dx){
						i = jmpLine;
						continue;
					}
				} else {
					int compNum = atoi(token);
					short shortNum = (short) compNum;
					if (ax <= shortNum){
						i = jmpLine;
						continue;
					}
				}
			} else if (strcmp(token, "bx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (bx <= ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (bx <= bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (bx <= cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(bx <= dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (bx <= shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "cx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (cx <= ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (cx <= bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (cx <= cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(cx <= dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (cx <= shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "dx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (bx <= ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (dx <= bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (dx <= cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(dx <= dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (dx <= shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else {
                               int xNum = atoi(token);
				short x2Num = (short) xNum;
				token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (x2Num <= ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (x2Num <= bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (x2Num <= cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(x2Num <= dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (x2Num <= shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        }
		//Subtract
		} else if (strcmp(token, "sub") == 0) {

                        token = strtok(NULL, " ");

                        if (strcmp(token, "ax") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax - ax;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx - ax;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx - ax;}
                                else { dx = dx - ax;}
                        } else if (strcmp(token, "bx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax - bx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx - bx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx - bx;}
                                else { dx = dx - bx;}
                        } else if (strcmp(token, "cx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax - cx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx - cx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx - cx;}
                                else { dx = dx - cx;}
                        } else if (strcmp(token, "dx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax - dx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx - dx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx - dx;}
                                else { dx = dx - dx;}
                        } else{
                                int srcNum = atoi(token);
                                short shortNum = (short) srcNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0) {ax = ax - shortNum;}
                                else if (strcmp(token, "bx\n") == 0) {bx = bx - shortNum;}
                                else if (strcmp(token, "cx\n") == 0) {cx = cx - shortNum;}
                                else {dx = dx - shortNum;}
                        }
			//printf("ins = sub, ax = %hi, bx = %hi, cx = %hi, dx = %hi\n", ax, bx, cx, dx); 

		//Multiply
		} else if (strcmp(token, "mul") == 0){
			
			token = strtok(NULL, " ");
			
			if (strcmp(token, "ax") == 0){
        			token = strtok(NULL, " ");
       				if (strcmp(token, "ax\n") == 0){ ax = ax * ax;}
				else if (strcmp(token, "bx\n") == 0){ bx = bx * ax;}
				else if (strcmp(token, "cx\n") == 0){ cx = cx * ax;}
				else { dx = dx * ax;}
    			} else if (strcmp(token, "bx") == 0){
				token = strtok(NULL, " ");
       				if (strcmp(token, "ax\n") == 0){ ax = ax * bx;}
				else if (strcmp(token, "bx\n") == 0){ bx = bx * bx;}
				else if (strcmp(token, "cx\n") == 0){ cx = cx * bx;}
				else { dx = dx * bx;}
   			} else if (strcmp(token, "cx") == 0){
				token = strtok(NULL, " ");
       				if (strcmp(token, "ax\n") == 0){ ax = ax * cx;}
				else if (strcmp(token, "bx\n") == 0){ bx = bx * cx;}
				else if (strcmp(token, "cx\n") == 0){ cx = cx * cx;}
				else { dx = dx * cx;}
    			} else if (strcmp(token, "dx") == 0){
				token = strtok(NULL, " ");
        			if (strcmp(token, "ax\n") == 0){ ax = ax * dx;}
				else if (strcmp(token, "bx\n") == 0){ bx = bx * dx;}
				else if (strcmp(token, "cx\n") == 0){ cx = cx * dx;}
				else { dx = dx * dx;}
			} else{
				int srcNum = atoi(token);
				short shortNum = (short) srcNum;
				token = strtok(NULL, " ");
				if (strcmp(token, "ax\n") == 0) {ax = ax * shortNum;}
				else if (strcmp(token, "bx\n") == 0) {bx = bx * shortNum;}
				else if (strcmp(token, "cx\n") == 0) {cx = cx * shortNum;}
				else {dx = dx * shortNum;}
			}
		//Print
		} else if (strcmp(token, "print") == 0){
			//printf("ins: print, i = %d, token = %s\n",i , token);
			token = strtok(NULL, " ");
			//printf("ins: print, i = %d, token = %s\n",i , token);
			if (strcmp(token, "ax\n") == 0) {printf("%hi", ax);}
			else if (strcmp(token, "bx\n") == 0) {printf("%hi", bx); }
			else if (strcmp(token, "cx\n") == 0) {printf("%hi", cx); }
			else if (strcmp(token, "dx\n") == 0) {printf("%hi", dx); }
			else { 
				int srcNum = atoi(token);
				printf("%d", srcNum);
			}
			//mov
		} else if (strcmp(token, "mov") == 0){

                        token = strtok(NULL, " ");

                        if (strcmp(token, "ax") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax;}
                                else if (strcmp(token, "bx\n") == 0){ bx = ax;}
                                else if (strcmp(token, "cx\n") == 0){ cx = ax;}
                                else { dx = ax;}
                        } else if (strcmp(token, "bx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = bx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = bx;}
                                else { dx = bx;}
                        } else if (strcmp(token, "cx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = cx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = cx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx;}
                                else { dx = dx;}
                        } else if (strcmp(token, "dx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = dx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = dx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = dx;}
                                else { dx = dx;}
                        } else{
                                int srcNum = atoi(token);
                                short shortNum = (short) srcNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0) {ax = shortNum;}
                                else if (strcmp(token, "bx\n") == 0) {bx = shortNum;}
                                else if (strcmp(token, "cx\n") == 0) {cx = shortNum;}
                                else {dx = shortNum;}
                        }
		} //Add 
		else if (strcmp(token, "add") == 0){

                        token = strtok(NULL, " ");

                        if (strcmp(token, "ax") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax + ax;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx + ax;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx + ax;}
                                else { dx = dx + ax;}
                        } else if (strcmp(token, "bx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax + bx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx + bx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx + bx;}
                                else { dx = dx + bx;}
                        } else if (strcmp(token, "cx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax + cx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx + cx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx + cx;}
                                else { dx = dx + cx;}
                        } else if (strcmp(token, "dx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax + dx;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx + dx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx + dx;}
                                else { dx = dx + dx;}
                        } else{
                                int srcNum = atoi(token);
                                short shortNum = (short) srcNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0) {ax = ax + shortNum;}
                                else if (strcmp(token, "bx\n") == 0) {bx = bx + shortNum;}
                                else if (strcmp(token, "cx\n") == 0) {cx = cx + shortNum;}
                                else {dx = dx + shortNum;}
                        }
		} //Divide	
		else if (strcmp(token, "div") == 0){

                        token = strtok(NULL, " ");

                        if (strcmp(token, "ax") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = ax / ax;}
                                else if (strcmp(token, "bx\n") == 0){ bx = ax / bx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = ax / cx;}
                                else { dx = ax / dx;}
                        } else if (strcmp(token, "bx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = bx / ax;}
                                else if (strcmp(token, "bx\n") == 0){ bx = bx / bx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = bx / cx;}
                                else { dx = bx / cx;}
                        } else if (strcmp(token, "cx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = cx / ax;}
                                else if (strcmp(token, "bx\n") == 0){ bx = cx / bx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = cx / cx;}
                                else { dx = cx / dx;}
                        } else if (strcmp(token, "dx") == 0){
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){ ax = dx / ax;}
                                else if (strcmp(token, "bx\n") == 0){ bx = dx / bx;}
                                else if (strcmp(token, "cx\n") == 0){ cx = dx / cx;}
                                else { dx = dx / dx;}
                        } else{
                                int srcNum = atoi(token);
                                short shortNum = (short) srcNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0) {ax = shortNum / ax;}
                                else if (strcmp(token, "bx\n") == 0) {bx = shortNum / bx;}
                                else if (strcmp(token, "cx\n") == 0) {cx = shortNum / cx;}
                                else {dx = shortNum / dx;}
                        }
		} //Jump if greater than or equal 
		else if ( strcmp(token, "jge") == 0) {
                        token = strtok(NULL, " ");
                        int jmpLine = atoi(token);
                        token = strtok(NULL, " ");

                        //Check if first number is register ax
                        if (strcmp(token, "ax") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (ax >= ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (ax >= bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (ax >= cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(ax >= dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax >= shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "bx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (bx >= ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (bx >= bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (bx >= cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(bx >= dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax >= shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "cx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (cx >= ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (cx >= bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (cx >= cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(cx >= dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (cx >= shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else {
                               int xNum = atoi(token);
                                short x2Num = (short) xNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (x2Num >= ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (x2Num >= bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (x2Num >= cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(x2Num >= dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (x2Num >= shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        }
		} //Jump if not equal 
		else if ( strcmp(token, "jne") == 0) {
                        token = strtok(NULL, " ");
                        int jmpLine = atoi(token);
                        token = strtok(NULL, " ");

                        //Check if first number is register ax
                        if (strcmp(token, "ax") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (ax != ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (ax != bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (ax != cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(ax != dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax != shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "bx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (bx != ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (bx != bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (bx != cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(bx != dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax != shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "cx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (cx != ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (cx != bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (cx != cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(cx != dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (cx != shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else {
                               int xNum = atoi(token);
                                short x2Num = (short) xNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (x2Num != ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (x2Num != bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (x2Num != cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(x2Num != dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (x2Num != shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        }
		} // Jump if equal 
		else if ( strcmp(token, "je") == 0) {
                        token = strtok(NULL, " ");
                        int jmpLine = atoi(token);
                        token = strtok(NULL, " ");

                        //Check if first number is register ax
                        if (strcmp(token, "ax") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (ax == ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (ax == bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (ax == cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(ax == dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax == shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "bx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (bx == ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (bx == bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (bx == cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(bx == dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax == shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "cx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (cx == ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (cx == bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (cx == cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(cx == dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (cx == shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else {
                               int xNum = atoi(token);
                                short x2Num = (short) xNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (x2Num == ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (x2Num == bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (x2Num == cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(x2Num == dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (x2Num == shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        }
		} // Jump if greater than
		else if ( strcmp(token, "jg") == 0) {
                        token = strtok(NULL, " ");
                        int jmpLine = atoi(token);
                        token = strtok(NULL, " ");

                        //Check if first number is register ax
                        if (strcmp(token, "ax") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (ax > ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (ax > bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (ax > cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(ax > dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax > shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "bx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (bx > ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (bx > bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (bx > cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(bx > dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (bx > shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "cx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (cx > ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (cx > bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (cx > cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(cx > dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (cx > shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "dx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (dx > ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (dx > bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (dx > cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(dx > dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (dx > shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                } 
			} else {
                               int xNum = atoi(token);
                                short x2Num = (short) xNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (x2Num > ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (x2Num > bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (x2Num > cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(x2Num > dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (x2Num > shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        }
		} //Jump if less then
		else if ( strcmp(token, "jl") == 0) {
                        token = strtok(NULL, " ");
                        int jmpLine = atoi(token);
                        token = strtok(NULL, " ");

                        //Check if first number is register ax
                        if (strcmp(token, "ax") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (ax < ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (ax < bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (ax < cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(ax < dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax < shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "bx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (bx < ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (bx < bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (bx < cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(bx < dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (ax < shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "cx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (cx < ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (cx < bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (cx < cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(cx < dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (cx < shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        } else if (strcmp(token, "dx") == 0) {
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (dx < ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (dx < bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (dx < cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(dx < dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (dx < shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
			} else {
                               int xNum = atoi(token);
                                short x2Num = (short) xNum;
                                token = strtok(NULL, " ");
                                if (strcmp(token, "ax\n") == 0){
                                        if (x2Num < ax){
                                                i = jmpLine;
                                                continue;
                                        }
                                }else if (strcmp(token, "bx\n") == 0 ) {
                                        if (x2Num < bx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "cx\n") == 0){
                                        if (x2Num < cx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else if (strcmp(token, "dx\n") == 0) {
                                        if(x2Num < dx){
                                                i = jmpLine;
                                                continue;
                                        }
                                } else {
                                        int compNum = atoi(token);
                                        short shortNum = (short) compNum;
                                        if (x2Num < shortNum){
                                                i = jmpLine;
                                                continue;
                                        }
                                }
                        }
		}
	i++;
	continue;
	}
	printf("\n");

}

//Scan function
void scan(short* y){
    printf("Enter number: ");
    short z = 0;
    scanf("%hd", &z);
    *y = z;
}
