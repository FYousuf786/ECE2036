#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class Task//struct Task converted to a class
{

private:
    int taskNum; //Each task will have a unique number
    std::string taskLeader; //Assume leader name is one string john_smith
    int beginOnDay; //This is the start day i.e. start of day 5 for example
    int taskDuration; //This is the number of days to complete
    std::string taskDescription; //This will be a sentence describing task

public:
	Task();
	Task(int num, string leader, int begin, int duration, string descr);
	void setTaskNum(int num);
	void setTaskLeader(string leader);
	void setBeginOnDay(int start);
	void setTaskDuration(int end);
	void setTaskDescription(string des);
	int getTaskNum();
	string getTaskLeader();
	int getBeginOnDay();
	int getTaskDuration();
	string getTaskDescription();

};

class Gantt
{
   public:
		
	   Gantt();//Gantt constructor

      void readInData(std::string); //This will have the file name
      void createHTMLFile(std::string); //This will have the outputfile name

   private: //These will be utility files used internally on this object so I will keep them private

      void startHTMLfile();
      void endHTMLfile();
      void insertHead();
      void insertBody();
      void beginBody();
      void endBody();
      void ganttChartHeaderInfo();
      void chartColumnLabels();
      void ganttChartBody();
      void taskCharts();

   private:

       std::vector <Task> taskList; //notice this is a vector of your user-defined type Task
       std::string projectName; //Single string name for project
       std::string beginDate;   //This is a calendar data that is needed.. just read in as a string from input file
       int durationInWeeks; //assume that integral number by definition in the problem
       int numberOfTeamMembers; 
       std::vector <std::string> teamMembers;
       int numTasks;
       std::string outFileName; //This will be needed 

};
