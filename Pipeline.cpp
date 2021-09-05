#include<iostream>
#include<fstream>

using namespace std;

int src1[32],src2[32],dest[32];
string ins[32];
int pipeline[128][128];
int stall=0;
int i=0,count=0;
int raw=0,war=0,waw=0;//flag
 ofstream myfile;
void disp_stall()
{
    stall=1;
    myfile<<"x"<<" ";
}

void data_fwd(int number_ins,string tmp_ins)
{
    if(raw==1 && tmp_ins!="LW")
    {
        myfile<<"Data Fowrarding: "<<ins[number_ins]<<" R"<<dest[number_ins]<<" L3[R"<<src1[number_ins]<<"] R"<<src2[number_ins]<<endl;
        raw=0;
    }
    if(waw==1)
    {
        stall=1;
    }
}

void print_ins()
{
    myfile<<"\n========Insterted Input============\n";
    for(int i=0; i<count;i++)
    {
        myfile<<i<<" "<<ins[i]<<" R"<<dest[i]<<" R"<<src1[i]<<" R"<<src2[i]<<endl;
    }
}
void war_disp(int tmp_war, int ins_set)
{
    if(raw==1){
    myfile<<"RAW Conflict between "<<ins[ins_set]<<" R"<<dest[ins_set]<<" R"<<src1[ins_set]<<" R"<<src2[ins_set]<<" and "<<ins[ins_set+1]<<" R"<<dest[ins_set+1]<<" R"<<src1[ins_set+1]<<" R"<<src2[ins_set+1]<<endl;
    raw=0;}
}
void check_hazards()
{
    myfile<<"\n\n======Hazards and its solution===========\n\n";
    int flag=1;
    for(int i=0; i<count;i++)
    {
        if(dest[i]==src1[i+1]|| dest[i]==src2[i+1]){
        myfile<<"RAW Conflict between "<<ins[i]<<" R"<<dest[i]<<" R"<<src1[i]<<" R"<<src2[i]<<" and "<<ins[i+1]<<" R"<<dest[i+1]<<" R"<<src1[i+1]<<" R"<<src2[i+1]<<endl;
        raw=1;
        data_fwd(i,ins[i]);
        }
        if(src1[i]==dest[i+1]|| src2[i]==dest[i+1]){war=1;war_disp(war,i);
        
        myfile<<"WAR Conflict between "<<ins[i]<<" R"<<dest[i]<<" R"<<src1[i]<<" R"<<src2[i]<<" and "<<ins[i+1]<<" R"<<dest[i+1]<<" R"<<src1[i+1]<<" R"<<src2[i+1]<<endl;
        }if(dest[i]==dest[i+1])
    {waw=1;
        myfile<<"WAW Conflict between "<<ins[i]<<" R"<<dest[i]<<" R"<<src1[i]<<" R"<<src2[i]<<" and "<<ins[i+1]<<" R"<<dest[i+1]<<" R"<<src1[i+1]<<" R"<<src2[i+1]<<endl;
    }flag=0;
    }
    if(flag==1)
    myfile<<"No Data Hazard Found!!"<<endl;

}

void print_pipeline()
{
    myfile<<"\n\n=========Pipeline Structure=================\n\n";
    int time_unit=0;
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<5+i;j++)
        {
            if(stall){
            disp_stall();
            stall=0;}
            myfile<<pipeline[i][j]<<" ";
        }
        myfile<<endl;
    }
}
void pipeline_struct()
{
    int time_unit=0;
    for(int i=0;i<count;i++)
    {
        int state =1;
        for(int j=i;j<i+5;j++)
        {
            pipeline[i][j]= state;
            state++;
        }
    }
    print_pipeline();
}

void take_input()
{
     while (1)
    {
    string temp_ins; int temp_dest,temp_src1,temp_src2;    
    cin>>temp_ins;
    if(temp_ins=="HLT" || temp_ins=="BRK")
    break;
   
    cin>>temp_dest>>temp_src1>>temp_src2;
    if(temp_dest>33 && temp_src1>33 && temp_src2>33)
        myfile<<"Enter Value Between 0-32 only"<<endl;
    else
    {
        ins[i]=temp_ins;
        dest[i]=temp_dest;
        src1[i]=temp_src1;
        src2[i]=temp_src2;
        count++;i++;
    }
    }
}
int main()
{

   
    myfile.open("output.txt");
    myfile<<"INSTRUCTION DEST_REG SRC1_REG SRC2_REG\n";
    take_input();
    print_ins();
    check_hazards();
    pipeline_struct();
    myfile.close();


    return 0;

}