#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


struct Edge;

struct Student
{
    int id;
    vector<Edge*> edges;

    bool matched = false;
    Edge* matchedEdge;

    int dist;
};

struct Project
{
    int id;
    vector<Edge*> edges;

    int freePlaces;

    int dist;
};

struct Edge
{
    Student* student;
    Project* project;
    int prio;
    bool matched = false;

    void addToMatching()
    {
        matched = true;
        student->matched = true;
        student->matchedEdge = this;
        project->freePlaces--;
    }

    void removeFromMatching()
    {
        matched = false;
        project->freePlaces++;
    }
};


int main()
{
    std::iostream::sync_with_stdio(false);
    cin.tie(NULL);
    //std::freopen("../sample.in", "r", stdin);
    //std::freopen("../largeSample.in", "r", stdin);


    int numStudents, numProjects, numPrios, peoplePerProject;
    cin >> numStudents >> numProjects >> numPrios >> peoplePerProject;
    int defaultPrio = 2 * numPrios;

    int prioPerStudent[numStudents][numPrios];
    for(int n=0; n<numStudents; ++n)
    {
        int studentID;
        cin >> studentID;
        for(int m=0; m<numPrios;++m)
        {
            int project;
            cin >> project;
            prioPerStudent[studentID][m] = project;
        }
    }

    //create projects
    vector<Project> projects;
    projects.resize(numProjects);
    for(int i=0; i<projects.size(); ++i)
    {
        projects[i].id = i;
        projects[i].freePlaces = peoplePerProject;

    }

    //create students
    vector<Student> students;
    vector<Edge*> edges;
    students.resize(numStudents);
    for(int i=0; i<numStudents; ++i)
    {
        //set id of current student
        students[i].id = i;

        //compute how much current students like all projects
        vector<int> prioPerProject;
        prioPerProject.resize(numProjects, defaultPrio);
        for(int rank=0; rank<numPrios; ++rank)
        {
            prioPerProject[prioPerStudent[i][rank]] = rank+1;
        }

        //create all Edges for this student
        for(int projID=0; projID < numProjects; ++projID)
        {
            auto edge = new Edge;
            edge->student = &students[i];
            edge->project = &projects[projID];
            edge->prio = defaultPrio - prioPerProject[projID];
            students[i].edges.push_back(edge);
            projects[projID].edges.push_back(edge);
            edges.push_back(edge);
        }
    }

    //augment matching n times to get to perfect matching
    for(int n=0; n<numStudents; ++n)
    {
        //bellman ford to find lightest augmenting path

        //data to reconstruct shortest path
        vector<Edge*> prevS;
        prevS.resize(numProjects);
        vector<Edge*> prevP;
        prevP.resize(numStudents);

        //use all unmatched students as starting points
        for(auto& student : students)
            student.dist = student.matched ? 268435456 : 0;
        for(auto& project : projects)
            project.dist = 268435456;

        //yens tuning
        vector<Edge*> freeEdges;
        vector<Edge*> matchedEdges;
        for(auto edge : edges)
        {
            if(edge->matched)
                matchedEdges.push_back(edge);
            else
                freeEdges.push_back(edge);
        }
        bool freeEdgesTurn = true;

        //real bellman ford algorithm stuff
        bool hasRelaxed = true;
        for(int i=0; i<numStudents && hasRelaxed; ++i)
        {
            //relax edges
            hasRelaxed = false;
            if(freeEdgesTurn)
            {
                for(Edge* edge : freeEdges) //direction from student to project
                {
                    if(edge->project->dist > edge->student->dist - edge->prio)
                    {
                        edge->project->dist = edge->student->dist - edge->prio;
                        prevS[edge->project->id] = edge;
                        hasRelaxed = true;
                    }
                }
            }
            else
            {
                for(Edge* edge : matchedEdges) //direction from project to student
                {
                    if(edge->student->dist > edge->project->dist + edge->prio)
                    {
                        edge->student->dist = edge->project->dist + edge->prio;
                        prevP[edge->student->id] = edge;
                        hasRelaxed = true;
                    }
                }
            }
            freeEdgesTurn = !freeEdgesTurn;
        }

        //project at end of shortest augmenting Path
        Project* minProject;
        for(auto& project : projects) //take first best
        {
            if(project.freePlaces > 0)
            {
                minProject = &project;
                break;
            }
        }
        for(auto& project : projects) //find real minimum
        {
            if(project.freePlaces > 0 && project.dist < minProject->dist)
                minProject = &project;
        }

        //construct path
        vector<Edge*> path;
        Edge* nextEdge = prevS[minProject->id];
        bool nextIsStudent = true; //to alternate

        while(nextEdge!=nullptr)
        {
            path.push_back(nextEdge);
            if(nextIsStudent)
                nextEdge = prevP[nextEdge->student->id];
            else
                nextEdge = prevS[nextEdge->project->id];

            nextIsStudent = !nextIsStudent;
        }
        assert(path.front()->matched == false);
        assert(path.front()->project->freePlaces > 0);
        assert(path.back()->matched == false);
        assert(path.back()->student->matched == false);

        //augment matching by lightest path
        for(Edge* edge : path)
        {
            if(edge->matched)
                edge->removeFromMatching();
            else
                edge->addToMatching();
        }
    }


    //print resulting matching
    for(auto& student : students)
    {
        cout << student.id << " " << student.matchedEdge->project->id << "\n";
    }
    cout.flush();

    return 0;
}
