#include<utility.h>

int noPages=0,noFrames=0,pagesIn[100],faultPage=0,currentSize = 0, repeated = 0;
int inputcompleted = 0;
char ans=' ';


void push(int val, int repArray[], int rep) {
	//pag yung value ay di 0 or present at hindi -10 which is null pag yung both condition na meet continue sya sa first slot 
	if (repeated == 0 && repArray[noFrames-1] != -10){ 
		// at nilalagay yung new val sa unang position ng array 
		repArray[0] = val; 
		//stop if nag true 
		return;
	} //loop for shifting 
    for (rep; rep > 0; rep--) {
        repArray[rep] = repArray[rep - 1];
    } 
    // maglalagay ng new value sa first slot after ng loop 
    repArray[0] = val;
}

void processPrint() {
    int row[100];
    int line = 5;
    faultPage = 0;
    repeated = 0;
    

    for (int x = 0; x < 100; x++) // Set all array value to -10
        row[x] = -10;
        
	//checking  
    for (int i = 0; i < noPages; i++) { // Per page
        for (int y = 0; y < noFrames; y++) { // Check existence per row
            if (pagesIn[i] == row[y])
                repeated = 1; // if nag exit yung page ilalagay nya sa repeated 1
        }
        if (repeated == 1) {
        	faultPage++;
            for (int y = 0; y < noFrames; y++) { // Check existence per row for pushing purposes 
                if (pagesIn[i] == row[y]) {
                    push(pagesIn[i], row, y); // pag nakita yung page na repeated pupush nya at 
                    repeated = 0; // reset sa zero yung repeated 
                    break;
                }
            }
        } else
            push(pagesIn[i], row, noFrames); // pero pag di naman nakita  add lang nya sa front 
        // printing 
        for (int x = 0; x < noFrames; x++) { // Prints value 
            gotoxy(2 + i * 4, 5 + x * 2); // Adjust spacing for two-digit numbers
            if (row[x] == -10)
                printf("  "); // Two spaces for empty cells
            else
                printf("%2d", row[x]); // Two-character-width cell for numbers
        }
    }
}
void inputPages(int start) {
    for (int x = 0; x < noPages;) {
        char input[10];//dito unang input papasok
        int valid = 1, value;

        gotoxy(2 + (x * 4), start + 1);
        printf("  "); 
        gotoxy(2 + (x * 4), start + 1);
        scanf("%s", input);// binabasa yung input as string para ma check if tama

		// checking if negative or numeric yung number
        for (int i = 0; input[i] != '\0'; i++) {
            if (!((i == 0 && input[i] == '-') || (input[i] >= '0' && input[i] <= '9'))) { 
                valid = 0;// mark as invalid kung non-numeric or valid negative
                // nag- aallow na pwede mag input ng negative  || checking kung di numeric yung nainput 
            }
            else {
             	continue;
             	break;
			 }
        }
        if (valid) {
            value = atoi(input); // convert ng string sa integer 

            if (value >= -9 && value <= 9) {
                pagesIn[x] = value;
                x++;
            } else {  // kung di valid yung number 0-9, buburahin tas pwede mag input ulit 
                gotoxy(2 + (x * 4), start + 1);
                settextcolor(12);center(20,"invalid!! double digit not allowed");settextcolor(7);
                Sleep(1000);clearportion(20,20,60,20);
                printf("  "); 
                gotoxy(2 + (x * 4), start + 1);
            }
        } else { // kung di valid yung number at character, buburahin tas pwede mag input ulit 
            gotoxy(2 + (x * 4), start + 1);
            settextcolor(12);center(20,"invalid!! double digit not allowed");settextcolor(7);
            Sleep(1000);clearportion(20,20,60,20);
            printf("  "); 
            gotoxy(2 + (x * 4), start + 1);
            printf("\b\b");
        }
    }
}
int makebox(int startY) {
    box3(0, startY, 4, startY + 2); // Adjust width to 4 units for two spaces per box
    for (int z = 0; z < noFrames; z++) {
        boxtab2(0, startY + 2 * (z + 1), 4, startY + 2 + 2 * (z + 1));
    }
    for (int x = 0; x < noPages - 1; x++) {
        boxright(4 * (x + 1), startY, 4 + 4 * (x + 1), startY + 2); // Adjust width
        for (int y = 0; y < noFrames; y++) {
            boxdownright(4 * (x + 1), startY + 2 * (y + 1), 4 + 4 * (x + 1), startY + 2 + 2 * (y + 1));
        }
    }
    return startY;
}

// ------------------------------

void mainrtn() {		
    system("cls");
    
     while (1) { // Loop for frame input
        printf("How many frames: ");
        if (scanf("%d", &noFrames) != 1) { // Check if input is not a number
            settextcolor(12);printf("Invalid input! Please enter a number.\n");settextcolor(7);
            Sleep(1500);
            clearportion(1, 1, 50, 1);
            fflush(stdin); // Clear invalid input
            system("cls");
            continue;
        }

        if (noFrames < 3 || noFrames > 6) { // Check if input is out of range
           settextcolor(12);printf("The frames should be between 3 and 6.\n");settextcolor(7);
            Sleep(1500);
            clearportion(1, 1, 50, 1);
            system("cls");
            continue;
        }
        break; // Valid input
    }

    while (1) { // Loop for reference string input
        system("cls");
        printf("How many frames: %d\n", noFrames); // Retain the frame input
        printf("How many reference strings: ");

        if (scanf("%d", &noPages) != 1) { // Check if input is not a number
            settextcolor(12);printf("Invalid input! Please enter a number.\n");settextcolor(7);
            Sleep(1500);
            clearportion(1, 1, 50, 1);
            fflush(stdin); // Clear invalid input
            system("cls");
            continue;
        }

        if (noPages < 10 || noPages > 25) {
            settextcolor(12);printf("The reference string size should be 10 to 25\n");settextcolor(7);
            Sleep(1500);
            system("cls"); // Clear the invalid message
            continue; // Retry input for reference strings
        }

        inputPages(makebox(2));
        processPrint();
        float Final = noPages - faultPage;
        gotoxy(0, 9 + (2 * (noFrames - 1)));
        printf("Page Fault %.f/%d = %.2f%%", Final, noPages, Final / noPages * 100);
        gotoxy(0, 24);

		inputcompleted = 1;
        break; // Exit loop after successful input
    }

    do {
        printxy(0, 20, "Input again? Y/N ");
        scanf(" %c", &ans);
        if (ans == 'Y' || ans == 'y') {
        	inputcompleted = 0;
            break; 
            
        } else if (ans == 'N' || ans == 'n') {
            system("cls");
            setColor(5);
            center(6, "       .__                               ");
			center(7, "______ |  |   ____ _____    ______ ____  ");
			center(8, "\\____ \\|  | _/ __ \\\\__  \\  /  ___// __ \\ ");
			center(9, "|  |_> >  |_\\  ___/ / __ \\_\\___ \\\\  ___/ ");
			center(10, "|   __/|____/\\___  >____  /____  >\\___  >");
			center(11, "|__|             \\/     \\/     \\/     \\/ ");
			center(13, "               .__  __   ");
			center(14, "__  _  ______  |__|/  |_ ");
			center(15, "\\ \\/ \\/ |__  \\ |  \\   __\\");
			center(16, " \\     / / __ \\|  ||  |  ");
			center(17, "  \\/\\_/ (____  /__||__|  ");
			center(18, "             \\/          ");
        	setColor(7);
            Sleep(1000);
            system("cls");
			break; 
        }
    } while (1);
}
	
void design(){
	box2(2,2,78,24);
    setColor(5);
    center(4, " __     __  ______  __      ______  ______  __    __  ______    ");
    center(5, "/\\ \\  _ \\ \\/\\  ___\\/\\ \\    /\\  ___\\/\\  __ \\/\\ \"-./  \\/\\  ___\\   ");
    center(6, "\\ \\ \\/ \".\\ \\ \\  __\\\\ \\ \\___\\ \\ \\___\\ \\ \\/\\ \\ \\ \\-./\\ \\ \\  __\\   ");
    center(7, " \\ \\__/\".~\\_\\ \\_____\\ \\_____\\ \\_____\\ \\_____\\ \\_\\ \\ \\_\\ \\_____\\ ");
    center(8, "  \\/_/   \\/_/\\/_____/\\/_____/\\/_____/\\/_____/\\/_/  \\/_/\\/_____/ ");
    center(9, "                                                                ");
    setColor(7);
    
	box3(28, 12, 50, 14);
	setColor(5);
	printxy(35,13, "A] Start");
	setColor(7);
    box3(28, 15, 50, 17);
    setColor(5);
    printxy(35,16, "B] Members");
    setColor(7);
    box3(28, 18, 50, 20);
    setColor(5);
    printxy(35,19,"C] Close");
    setColor(7);
    
    center(22,"Select an Option");
	gotoxy(50,22);

	ans=toupper(getche());
}

void members()
{
			system("cls");
			box2(2,2,78,24);
			
			setColor(7);
			center(3, "                   __             ");
			center(4, "  __ _  ___ __ _  / /  ___ _______");
			center(5, " /  ' \\/ -_)  ' \\/ _ \\/ -_) __(_-<");
			center(6, "/_/_/_/\\__/_/_/_/_.__/\\__/_/ /___/");
			
			setColor(5);
			printxy(8, 8, "      _     _    ");
			printxy(8, 9, "     (c).-.(c)   ");
			printxy(8, 10, "      / ._. \\    ");
			printxy(8, 11, "    __\\( Y )/__   ");
			printxy(8, 12, "   (_.-/'-\\-._)   ");
			printxy(8, 13, "     ||Borgy||    ");
			printxy(8, 14, "    _.' -' '._   ");
			printxy(8, 15, "   (.-./-\\.-.)   ");
			printxy(8, 16, "    -'     -'   ");
			setColor(7);		
			setColor(13);		
			printxy(29, 8, "      _     _    ");
			printxy(29, 9, "     (c).-.(c)   ");
			printxy(29, 10, "      / ._. \\    ");
			printxy(29, 11, "    __\\( Y )/__   ");
			printxy(29, 12, "   (_.-/'-\\-._)   ");
			printxy(29, 13, "    ||Tyronne||    ");
			printxy(29, 14, "    _.' -' '._   ");
			printxy(29, 15, "   (.-./-\\.-.)   ");
			printxy(29, 16, "    -'     -'   ");
			setColor(7);
			setColor(10);
			printxy(50, 8, "      _     _    ");
			printxy(50, 9, "     (c).-.(c)   ");
			printxy(50, 10, "      / ._. \\    ");
			printxy(50, 11, "    __\\( Y )/__   ");
			printxy(50, 12, "   (_.-/'-\\-._)   ");
			printxy(50, 13, "    ||Bernardo||    ");
			printxy(50, 14, "    _.' -' '._   ");
			printxy(50, 15, "   (.-./-\\.-.)   ");
			printxy(50, 16, "    -'     -'   ");
			setColor(7);
			
			center(23,"Back home ....");
			_getch();	
}
main()
{
	//system("Color 05");
	
	box2(19,4,59,20);
	
	setColor(5);
    center(6, "______  _______________  __");
    center(7, "___   |/  /__  __ \\_  / / /");
    center(8, "__  /|_/ /__  /_/ /  / / / ");
    center(9, "_  /  / / _  _, _// /_/ /  ");
    center(10, "/_/  /_/  /_/ |_| \\____/   ");
    setColor(7);
    
    center(14,"Press any key. . . . .");
	_getch();
	
	while(ans!='C')
{
    system("cls");
	design();
	if(ans=='A')
			{
            while (1) 
			{
                mainrtn();
                if (inputcompleted) 
				break; 
				 
            }
      	    }
	else if (ans=='B')
		{
			members();
		}
	else if (ans == 'C')
		{
			system("cls");
			setColor(5);
            center(2, "   __  __                __                       ");
        	center(3, "  / /_/ /_  ____ _____  / /__   __  ______  __  __ ");
        	center(4, " / __/ __ \\/ __ `/ __ \\/ //_/  / / / / __ \\/ / / / ");
        	center(5, "/ /_/ / / / /_/ / / / / ,<    / /_/ / /_/ / /_/ /  ");
       	 	center(6, "\\__/_/ /_/\\__,_/_/ /_/_/|_|   \\__, /\\____/\\__,_/   ");
        	center(7, "                             /____/                 ");
        	setColor(7);
			exit;
		}
	else
		{
			clearportion(10,22,60,22);
			settextcolor(12);
			center(22,"Invalid option, try again...");
			settextcolor(7);
			Sleep(1000);
		}
}	
}
