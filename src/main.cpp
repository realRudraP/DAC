#include<iostream>
#include<string>

int main(){
    std::cout<<"Discretionary Access Control: Linked List\n";
    std::cout<<"(Create Access Policy Mode)\n";
    std::cout<<"Commands:\n";
    std::cout<<"\tCreate Subject <Subject name>\n\tCreates <Object Type> <Object Name>\n";
    std::cout<<"\tGrant <Subject Name> <Object Name> [List of Rights]\n";
    std::cout<<"\tRevoke <Subject Name> <Object Name> [List of Rights]\n";
    std::cout<<"\tCheck <Subject Name> <Object Name> <Right>\n";
    std::cout<<"\tPolicy\n";
    std::cout<<"\tDone (Finish creating policies)\n";

    std::string inputLine;
    while (true)
    {
        std::cout<<"Create ACL> ";
        if(!std::getline(std::cin,inputLine)){
            std::cerr<<"Error in input from console"<<std::endl;
        }

        
    }
    
    return 0;
}