#include <iostream>
#include <fstream>


#include "gantt.h"

#define OFFSET 50
#define TABLE_OVERHEAD 6

using namespace std;
Task::Task() {} //default Task construct (formerly a structure, class defined in gantt.h)
Task::Task(int num, string leader, int begin, int duration, string descr): taskNum(num), taskLeader(leader), beginOnDay(begin), taskDuration(duration), taskDescription(descr) {} //parameterized constructor that initializes private members (used in Gantt::readinData)
Gantt::Gantt() {}//Gantt constructor (class defined in gantt.h)

void Gantt::readInData(string inputFileName) 
{
    //This member function will read in data from the input file that describes the project
    //The format of this file should be evident from the example input.txt provided to you.

    ifstream inFileObject(inputFileName.c_str(), ios::in); //defines file object to read from .txt file
    string trash;//a temporary string used to parse out uneccessary data

	//everything before a space in a line is place in "trash", remaining data is placed in the variable after extraction operator
    inFileObject >> trash >> projectName;  //Assume project name is a single string! 
    inFileObject >> trash >> beginDate; 
    inFileObject  >> trash >> durationInWeeks; 
    inFileObject >> trash >> numberOfTeamMembers;


	teamMembers.resize(numberOfTeamMembers);//resize the teamMembers vector according to number defined in .txt
	for (int i = 0; i < numberOfTeamMembers; i++) {
		inFileObject >> trash >> teamMembers[i];//Team_Member_#: is placed in "trash", Name is placed in teamMembers[i]
	}

 
    inFileObject >> trash >> numTasks;//Number_of_Tasks: is placed in "trash", actual value is placed in numTasks

	//define variables of old structure for temporary use
	int taskNum;
	string taskLeader;
	int beginOnDay;
	int taskDuration;
	string taskDescription;
	
	//taskList is vector of Task class objects
	taskList.resize(numTasks);//resize the vector to have the appropriate number of tasks
	for (int i = 0; i < numTasks; i++) {
		inFileObject >> trash >> taskNum;//"Task_Num: " placed in "trash", taskNum is Task Number
		inFileObject >> trash >> taskLeader;//"Task_Leader: " placed in "trash", taskLeader is a team member
		inFileObject >> trash >> beginOnDay;//"Task_Begin_on_Day:" placed in "trash", beginOnDay is start day (as integer)
		inFileObject >> trash >> taskDuration;//"Task_Duration_Days:" placed in "trash", taskDuration is length of task (as integer)
		inFileObject >> trash;//Task_Description:  placed in "trash"
		getline(inFileObject, taskDescription);// taskDescription is description of task

		Task temp(taskNum, taskLeader, beginOnDay, taskDuration, taskDescription); // create a temporary Task class object with all appropriate values passed to their private variables
		taskList[i] = temp;//copy temporary class into vector of Task objects
	}


	/*ORIGINAL STRUCT IMPLEMENTATION
    taskList.resize(numTasks);
 
    for (int i = 0; i < numTasks; i++)
    {
       inFileObject >> trash >> taskList[i].taskNum;
       inFileObject >> trash >> taskList[i].taskLeader;
       inFileObject >> trash >> taskList[i].beginOnDay;
       inFileObject >> trash >> taskList[i].taskDuration;
       inFileObject >> trash; 

       getline(inFileObject, taskList[i].taskDescription);
    }
	*/
        
//ORIGINAL STRUCT IMPLEMENTATION

    inFileObject.close(); //close input .txt file object 
};

void Gantt::createHTMLFile(string outputFileName)
{
   //This function will create the output HTML file that will
   //represent your Gantt Chart. You will need to make sure
   //that you get all of these member functions working properly
   //in this skeleton code.  I broke the tasks into subtask to 
   //help make this member function easier to debug and understand.

   //NOTE you may have to comment these out as you get each 
   //one working!!! Remember the incremental design approach!

    outFileName = outputFileName; //This will be used often

    startHTMLfile();
    insertHead();
    beginBody();
    ganttChartHeaderInfo();
    chartColumnLabels();
    ganttChartBody();
    taskCharts();
    endBody();
    endHTMLfile();
   
}

void Gantt::insertHead()
{
	ifstream headHTMLObject("head.html", ios::in);//open provided "head.html" to read 
    ofstream outputFileObject(outFileName.c_str(), ios::app);//open new file object to write new .html file
	char temp;//define temporary char variable to copy "head.html" to the output file character by character

	while (headHTMLObject && headHTMLObject.get(temp)) {//while the head file object isn't null AND there are more characters to read in the file 
		outputFileObject.put(temp);//place the temporary character into the output file
	}

    //------------------ ADDITION NEEDED BY STUDENT -----------------------
    //This member function will read in the file called
    // head.html and put the contents into the output file
    // that is being created. This should be a simple task
    // so I would like for you to complete this.  
    // For all your html files, the header will also be the
    // same. No need to change the html script, please just put this
    // in your output html file! You may hard code in the name of 
    // the head.html. Notethat this is one of the files that I 
    // have provided to you in the tarfile
     
	headHTMLObject.close();//close the "head.html" file
    outputFileObject.close();//close the output file
}


void Gantt::startHTMLfile()
{
    //You do not need to change this member function 

    ofstream outputFileObject(outFileName.c_str(), ios::out);
    outputFileObject << "<html>" << endl;
    outputFileObject.close();
}

void Gantt::endHTMLfile()
{
   //You do not need to change this member function 

    ofstream outputFileObject(outFileName.c_str(), ios::app);
    outputFileObject << "</html>" << endl;
    outputFileObject.close();
}

void Gantt::beginBody()
{
   //You do not need to change this member function 

    ofstream outputFileObject(outFileName.c_str(), ios::app);
    outputFileObject << "<body>" << endl;
    outputFileObject.close();
}

void Gantt::endBody()
{
   //You do not need to change this member function 

    ofstream outputFileObject(outFileName.c_str(), ios::app);
    outputFileObject << "</body>" << endl;
    outputFileObject.close();
}

void Gantt::ganttChartHeaderInfo()//copies appropriate data to the chart's header
{

    ofstream outputFileObject(outFileName.c_str(), ios::app);//open output file to append to the end

   
    // According to the specification of the lab the tableWidth should be numberofWeeks*210+50 to get good spacing

    int tableWidth= durationInWeeks * 210 + 50; //initialize this with the formula as specified above 

    outputFileObject << "<table style=\"width: " << tableWidth << "px\">" << endl;//place tableWidth in output html

   //------------------ ADDITION NEEDED BY STUDENT -----------------------
   //I got you started. You finish the rest to create the top of the html page
   // Project Name: XXXX
   // Begin Date:  XXXX
   // Project Duration: XXXX
   // Team Members: XXXX

	//Project Name
	outputFileObject << "<tr>" << endl;
	outputFileObject << "<td colspan = \"2\"> Project Name: " << projectName << "</td>"<< endl;
	outputFileObject << "</tr>" << endl;
	//Date
	outputFileObject << "<tr>" << endl;
	outputFileObject << "<td colspan = \"2\"> Begin Date : " << beginDate << "</td>" << endl;
	outputFileObject << "</tr>" << endl;
	//Duration
	outputFileObject << "<tr>" << endl;
	outputFileObject << "<td colspan = \"2\"> Project Duration : " << durationInWeeks << " weeks"<< "</td>" << endl;
	outputFileObject << "</tr>" << endl;
	//Team Members
	outputFileObject << "<tr>" << endl;
	outputFileObject << "<td colspan = \"2\"> Team Members: ";
	
	//for loop writes list of team members
	for (int i = 0; i < numberOfTeamMembers; i++) {//iterate for the number of team members
		outputFileObject << teamMembers[i];//place current member into output html
		if (i < (numberOfTeamMembers - 1)) {//if we aren't at the last member; append a comma
			outputFileObject << ", ";//add comma to html output
		}
		else {
			outputFileObject << "</td>" << endl;
		}
	}
	outputFileObject << "</tr>" << endl;

    outputFileObject.close();
}

void Gantt::chartColumnLabels()
{
   //This function will create the labels for the Gantt chart
   // Some of this is a little tedious, but I will get you started.
   // You may edit anything in the function if you feel it is necessary
   
    ofstream outputFileObject(outFileName.c_str(), ios::app);

    int tableWidth = 210* durationInWeeks + OFFSET;
   
   outputFileObject << "<tr> \n\t <td style = \"height: 30px;\">\n </td>\n</tr>\n" << endl;

   outputFileObject << "<td style=\"width: 50px; vertical-align: bottom; border: dotted 1px grey;\"> "
                    << "<b> Task Label </b> </td> " << endl;

   outputFileObject << "<td style=\"width:" << tableWidth-OFFSET+TABLE_OVERHEAD 
                    <<"px; vertical-align: bottom;\">" << endl;
 
   // The colspan needs to be the number of days each week 
   // The width of the nested table needs to be numWeeks*210px
   outputFileObject << "<table style=\"width: " << tableWidth-OFFSET+TABLE_OVERHEAD  //replace tablewidth
                    << "px; border: dotted 1px grey;\">" << endl;
   
   //First the headers for the number of weeks in your project 
   //For simplicity, assume that the number of weeks is ALWAYS a whole number
   outputFileObject << "<tr>";

   for (int i=1; i <= durationInWeeks; i++)
   {
      outputFileObject << "<td colspan=\"7\" style=\"text-align: center ; "
                       << "width:210px; border: solid 1px black;\">"
                       << "Week " << i << "</td>" << endl;
   } 
   outputFileObject << "</tr>";


   outputFileObject << "<tr>" <<endl;

   // Insert your code here! 
   //Define row of days/column headers
   vector <string> days{ "Mon", "Tue", "Wed", "Thu", "Fri","Sat","Sun" };//create vector of days
   for (int j = 0; j < (durationInWeeks*7); j++) {//loop for the total number of days
	   if ((j%2)==0){//if j is even use "day", if odd use "day2"
		   outputFileObject << "<td class = \"day\"><b>" << days[j%7] << "</b></td>" << endl;//places appropriate day of the week
		   
	   }
	   else {
		   outputFileObject << "<td class = \"day2\"><b>" << days[j%7] << "</b></td>" << endl;//places appropriate day of the week
	   }
   }




   outputFileObject << "</tr>";
   outputFileObject << "</table>";

   outputFileObject << "</td>";
   outputFileObject << "</tr>";

    outputFileObject.close();
}

void Gantt::ganttChartBody()
{
    ofstream outputFileObject(outFileName.c_str(), ios::app);

 

   int i = 0;

   for (i=0; i < numTasks ; i++)//loop for the total number of tasks
   {
      outputFileObject << "<tr>"<<endl;
      outputFileObject <<"<td style=\"border:dotted 1px grey;\"> Task " << taskList[i].getTaskNum() << "</td>" << endl;//inserts "Task #"
      outputFileObject <<"<td style=\"border: dotted 1px grey;\">" << endl;
      outputFileObject << "<img src=\"dot_trans.gif\" height=\"15px;\" width=\""
                       << 30*(taskList[i].getBeginOnDay()-1) << "px;\">" << endl;//calculates length of duration (starting position)
    
      if (i%2 == 0) //if even then print gold bar
      { 
         outputFileObject << "<img src=\"gold.png\" height=\"15px;\" width=\""
                    << 30*taskList[i].getTaskDuration() << "px;\">" << endl;//calculates length of duration (ending position)
      }
      else//else print black bar
      {
         outputFileObject << "<img src=\"black.png\" height=\"15px;\" width=\""
                    << 30*taskList[i].getTaskDuration() << "px;\">" << endl;//calculates length of duration (ending position)
      }

      outputFileObject << "</td>"<<endl;
      outputFileObject << "</tr>"<<endl;
   }

   outputFileObject.close();

}


void Gantt::taskCharts()
{
   
    ofstream outputFileObject(outFileName.c_str(), ios::app);


    // Please NOTE that This lower table has the same width as the top table


    outputFileObject << "</table>" << endl; 
	outputFileObject << "<br>" << endl << "<br>" << endl;
	int tableWidth = durationInWeeks * 210 + 50; //initialize this with the formula as specified above in ganttChartHeaderInfo

	outputFileObject << "<table style=\"width: " << tableWidth << "px;\">" << endl;//set table width
	outputFileObject << "<tr>"<<endl;
	outputFileObject << "<td> Task <br> Label </td>"<<endl;//
	outputFileObject << "<td> Task Leader </td>" << endl;
	outputFileObject << "<td> Task Description </td>" << endl;
	outputFileObject << "</tr>" << endl;

	for (int i = 0; i < numTasks; i++) {
		outputFileObject << "<tr>" << endl;
		outputFileObject << "<td> <b> Task " << to_string(i+1) << "</b> </td>" << endl;
		outputFileObject << "<td> " << taskList[i].getTaskLeader() << " </td>" << endl;
		outputFileObject << "<td> " << taskList[i].getTaskDescription() << " </td>" << endl;
		outputFileObject << "</tr>" << endl;
	}
	outputFileObject << "</table>" << endl;
}

void Task::setTaskNum(int num) {
	taskNum = num;
}
void Task::setTaskLeader(string leader) {
	taskLeader = leader;
}
void Task::setBeginOnDay(int start) {
	beginOnDay = start;
}
void Task::setTaskDuration(int end) {
	taskDuration = end;
}
void Task::setTaskDescription(string des) {
	taskDescription = des;
}
int Task::getTaskNum() {
	return(taskNum);
}
string Task::getTaskLeader() {
	return(taskLeader);
}
int Task::getBeginOnDay() {
	return(beginOnDay);
}
int Task::getTaskDuration() {
	return(taskDuration);
}
string Task::getTaskDescription() {
	return(taskDescription);
}

