#include <bits/stdc++.h>
using namespace std;

map<string, int> grade;
map<int,vector<vector<string> > > details;
vector<float> tgp;

int sem_no;
int sem = 1;

string gradepoint(int marks)
{
	if (marks >= 90)
		return "O";
	if (marks >= 80)
		return "A+";
	if (marks >= 70)
		return "A";
	if (marks >= 60)
		return "B+";
	if (marks >= 50)
		return "B";
	if (marks > 40)
		return "C";
	if (marks == 40)
		return "D";
	return "E";
}

ofstream &operator<<(ofstream &ofs, map<int, vector<vector<string> > > &myMap)
{
	ofs << sem_no << endl;
	map<int,vector<vector<string> > >::iterator itr;
	for (itr = myMap.begin(); itr != myMap.end(); itr++)
	{
		vector<vector<string> > v1 = itr->second;
		for (int j = 0; j < v1.size(); j++)
		{
			for (int k = 0; k < v1[j].size(); k++)
				ofs << v1[j][k] << endl;
		}
		itr->second = v1;
	}
	return ofs;
}

int main()
{
	grade["O"] = 10;
	grade["A+"] = 9;
	grade["A"] = 8;
	grade["B+"] = 7;
	grade["B"] = 6;
	grade["C"] = 5;
	grade["D"] = 4;
	grade["E"] = 0;
	
	int num=0;
	string str;
	ifstream infile;
	infile.open("CGPA_Details.txt");
	if(infile){
		getline(infile,str);
		while(!infile.eof()){
			if(str[0]>='1' and str[0]<='9'){
				num=str[0]-'0';
			}
			infile>>str;
		}
		if(str[0]>='1' and str[0]<='9'){
			num=str[0]-'0';
		}
	}
	
	if(num!=0){
		sem=num + 1;
	}
	infile.close();
	
	cout<<sem<<endl;
	int choice;
	do
	{
	    cout<<setw(70)<<"***CGPA CALCULATOR***"<<endl<<endl;
	    cout<<setw(68)<<"Select one option"<<endl;
		cout <<setw(50)<< "1. Show CGPA" <<setw(40)<< "2. Show previous semester TGPA" << endl;
		cout <<setw(55)<< "3. Calculate TGPA" <<setw(42)<< "4. Show all semester grade and marks "<<endl;
		cout<<setw(45)<<"5. Exit"<<endl;
		cout<<"Enter you choice: ";
		cin >> choice;
		switch (choice)
		{
		    case 2:
		    {
		        int semNo;
		        cout<<"Enter sem no: ";
		        cin>>semNo;
		        if(tgp.size()<semNo) cout<<"Sem does not exist."<<endl;
		        else{
		            cout<<"TGPA of Sem "<<semNo<<" is "<<tgp[semNo-1]<<endl;
		        }
		    }
		    break;
		    case 1:
		    {
		        float sum=0;
		        vector<float>::iterator itr;
		        for(itr=tgp.begin();itr!=tgp.end();itr++){
		            sum+=*itr;
		        }
		        cout<<"CGPA till Sem "<<tgp.size()<<" is "<<sum/tgp.size()<<endl;
		    }
		    break;
		    case 4:
		    {
		        map<int,vector<vector<string> > >::iterator itr3;
		        if(details.empty()==0){
		            int sno=1;
		            for (itr3 = details.begin(); itr3 != details.end(); itr3++)
	                {
		                vector<vector<string> > v2 = itr3->second;
		                cout<<"Sem "<<sno<<" details"<<endl;
		                cout<<"TGPA: "<<tgp[sno-1]<<endl;
		                cout<<"Subject\t"<<"Grade"<<endl;
		                for (int j = 0; j < v2.size(); j++)
		                {
			                for (int k = 0; k < v2[j].size(); k++)
				                cout << v2[j][k] <<"\t";
		                }
		                cout<<endl;
		                itr3->second = v2;
		                sno++;
	                }
		        }else{
		            cout<<"No sem exists";
		        }
		    }
		    break;
		 case 3:
		    {
				map<int, vector<vector<string> > > myMap;
				vector<vector<string> > grade_details;
				map<string, int> credit;
				map<string, string> v;
				int no_of_subjects;
				cout << "Enter no of subjects: " << endl;
				cin >> no_of_subjects;
				//sub.push_back(no_of_subjects);
				string subject_code;
				int sub_credit;
				while (no_of_subjects--)
				{
					cout << "Enter the subject code: ";
					cin >> subject_code;
					cout << "Enter the credit for " << subject_code << ": ";
					cin >> sub_credit;
					credit[subject_code] = sub_credit;
					cout << endl;
				}
				int total_credit = 0;
				map<string,int>::iterator itr;
				for ( itr = credit.begin(); itr != credit.end(); itr++)
				{
					total_credit += itr->second;
				}
				int credit_sum = 0;
				int marks;
				int gpoint;
				map<string, int>::iterator it;
				for (it = credit.begin(); it != credit.end(); it++)
				{
					cout << "Enter the total marks of the subject " << it->first << ": ";
					cin >> marks;
					string cgrade = gradepoint(marks);
					grade_details.push_back({it->first, cgrade});
					v[it->first]=cgrade;
					map<string, int>::iterator itr1 = grade.find(cgrade);
					gpoint = itr1->second;
					credit_sum += (gpoint * it->second);
					cout << credit_sum << endl;
				}
				myMap[sem] = grade_details;
				details[sem]=grade_details;
				sem_no = sem;
				sem++;
				float tgpa=float(credit_sum) / float(total_credit);
				cout<<"TGPA is: "<<setprecision(3)<<tgpa<<endl;
				tgp.push_back(tgpa);
				cout << "Course\t"<< "Grade" << endl;
				map<string, string>::iterator i;
				for (i=v.begin();i!=v.end();i++)
				{
					cout << i->first << "\t" << i->second << endl;
				}
				ofstream outfile;
				outfile.open("CGPA_Details.txt", ios::app);
				outfile << myMap;
				outfile.close();
		    	}
			break;
			case 5:
			    break;
			default:
			    cout<<"Enter correct choice: ";
		}

	} while (choice != 5);
	return 0;
}

