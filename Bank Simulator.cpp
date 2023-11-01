//#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>  //for random generating
#include <fstream>   //for file editing commands
#include <vector>
#include <queue>
#include <iomanip>   //for setw usage
using namespace std;

//---------------------------------------------------------------------------------------------------//

const int maxName = 50;
const int maxMoney = 7;
const int maxNumber = 5;
const string sep = " |";
const int totalLen = maxName + maxNumber + maxMoney + sep.size() * 3;
const string sepLine = sep + string(totalLen - 1, '=') + '|';

class Bank
{
    public:
        unsigned long long account_number;
		char holder_name[51];
        int deposit;
        void System_clear();
		void Get_Data();
		void Write_Data();
		void deposit_withdraw(int n, int option);
		void Display_Individual_Records(long long n);
		void report() const;
		void Show_account() const; //to display account details
		void dep(int); //to add in deposit
		void draw(int x); //to subtract from deposit
		unsigned long long retAcNo() const; //function to return account number
		char retName() const; //function to return name
		int retdeposit() const; //function to return balance amount
		void Modification_data();
};
enum Color {RED, BLACK};

struct Node
{
	Bank data;
	bool color;
	Node *left, *right, *parent;

	// Constructor
	Node(Bank data)
	{
	this -> data = data;
	left = right = parent = NULL;
	this -> color = RED;
	}
};

// Class to represent Red-Black Tree
class RBTree
{
private:
	Node *root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixViolation(Node *&, Node *&);
public:
	// Constructor
	RBTree() {root = NULL;}
	void insert(const Bank &data);
	void inorder();
	void levelOrder();
};
RBTree r;


void Bank::Get_Data()
{
    cout << "\n\n===========CREATE BANK ACCOUNT===========\n\n";
    cout << "\nEnter the Account Number:";
	cin >> account_number;
	while ((int)to_string(account_number).size() != 5)  // Restrict account number to be of 12 digits
	{
		cout << "The account number has to be of 5 digits. Please try again.\n";
		cin.clear();    // Chances of unwanted newline in the buffer
		fflush(stdin);
		cin >> account_number;
	}
//    ac=account_number=00000
//    if (ac=<99999)
//    {
//        ac+=1
//    }
    cout << "\n\nEnter Account Holder Name: ";
    cin.clear();
	fflush(stdin);
    cin.getline(holder_name, 51);
    //showing error if in file
//    string x;
//    x=cin.getline(holder_name, 51);
//
//    Bank call;
//    ifstream inFile;
//    inFile.open("account.dat", ios::binary);
//    if (!inFile)
//        {
//        continue;
//        }
//    else
//    {
//       while (inFile.read((char * ) this, sizeof( * this)))
//    {
//        if (retName()==x)
//            {
//            cout << "\nThis name is used, please enter a new name!";
//            cin.getline(holder_name, 51);
//            }
//    }
//    }
//    inFile.close();

    cout << "\nEnter the Initial Amount for your Account: ";
    cin >> deposit;
//    while (deposit >= 1000000)
//    {
//        cout << "Maximum money is 1000000/-\nPlease try again: ";
//        cin >> deposit;
//    }
    cout << "\n\nAccount has been Created Successfully.";
}

void Bank::Write_Data()
{
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    Get_Data();
    outFile.write((char * ) this, sizeof( * this));
    outFile.close();
}

void Bank::Modification_data()
{
    cout << "\nAccount No: " << account_number;
    cout << "\nModify Account Holder Name: ";
    cin.clear();
	fflush(stdin);
    cin.getline(holder_name, 51);
    cout << "\nModify Total Balance Amount : ";
    cin >> deposit;
//	while (deposit >= 1000000)
//	{
//        cout << "Maximum money is 1000000/-\nPlease try again: ";
//        cin >> deposit;
//	}
}

void Bank::Display_Individual_Records(long long n)
{
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "\n\nNo data available!";
        return;
        }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read((char * ) this, sizeof( * this)))
    {
        if (retAcNo() == n)
            {
            Show_account();
            flag = true;
            }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccounts Details not Found.";
}

void Bank::report() const
{
    cout << sep <<
        setw(maxNumber) << account_number << sep <<
        setw(maxName) << holder_name << sep <<
        setw(maxMoney) << deposit << sep << endl << sepLine << endl;
}

void Bank::dep(int x)
{
    deposit = deposit + x;
}

void Bank::draw(int x)
{
    deposit -= x;
}

void Bank::Show_account() const
{
    cout << "\nAccount No: " << account_number;
    cout << "\nAccount Holder Name: ";
    cout << holder_name;
    cout << "\nTotal Balance: " << deposit;
}

unsigned long long Bank::retAcNo() const
{
    return account_number;
}

char Bank::retName() const
{
    return holder_name[51];
}

int Bank::retdeposit() const
{
    return deposit;
}

void Bank::System_clear()
{
    system("cls");
}

//-------------------------------------------------------------------------------------------------------//
void Delete_Account(unsigned long long n)
{
    Bank call;
    bool found = false;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "No data available!";
        return;
        }

    while (!inFile.eof() && found == false)
    {
        inFile.read((char * ) & call, sizeof(Bank));
        if (call.retAcNo() == n)
        {
            outFile.open("account_temp.dat", ios::binary);
            inFile.seekg(0, ios::beg);
            while (inFile.read((char * ) & call, sizeof(Bank)))
                {
                if (call.retAcNo() != n)
                {
                    outFile.write((char * ) & call, sizeof(Bank));
                }
                }
            inFile.close();
            outFile.close();
            remove("account.dat");
            rename("account_temp.dat", "account.dat");

            cout << "\n\nRecord has been Deleted.";
            found = true;
        }
    }
    inFile.close();

    if (found == false)
        cout << "\n\n Record Not Found.";
}

void system_clear()
{
    system("cls");
}

void Get_All_Data()
{
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "No data available!";
        return;
        }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "AC NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
    while (inFile.read((char * ) & call, sizeof(Bank)))
        {
        call.report();
        }
    inFile.close();
}

void Get_minus()
{
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "No data available!";
        return;
        }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "AC NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
    while (inFile.read((char * ) & call, sizeof(Bank)))
        {
        if(call.deposit < 0)
            call.report();
        }
    inFile.close();
}

void Lottery()
{
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "No data available!";
        return;
        }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "AC NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
        vector<Bank> bb;

    while (inFile.read((char * ) & call, sizeof(Bank)))
        {
            if(call.deposit > 0 )
            {
                bb.push_back(call);
            }
        }

    srand(time(NULL));
    int r = (rand() % (bb.size()-1));
    bb[r].report();
    int Award = (rand() % (bb[r].deposit));
    cout<<"\nAward : "<<  Award << endl;

    inFile.close();


    int amt;
    fstream File;
    File.open("account.dat", ios::binary | ios:: in | ios::out);
    while (!File.eof())
        {
        File.read((char * ) & call, sizeof(Bank));
        if (call.retAcNo() == bb[r].account_number)
            {
                cout << "\n\n===========DEPOSIT TO ACCOUNT===========";
                amt = Award;
                call.dep(amt);
                call.Show_account();

                int pos = (-1) * sizeof(call);
                File.seekp(pos, ios::cur);
                File.write((char * ) & call, sizeof(Bank));
                cout << "\n\nAccount Records Updated Successfully.";
           }
        }
    File.close();
}

void Del_minus()
{
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "No data available!";
        return;
        }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "AC NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
        vector<unsigned long long> ids;
    while (inFile.read((char * ) & call, sizeof(Bank)))
        {
        if(call.deposit < 0)
            {
                ids.push_back(call.account_number);
                call.report();
            }
        }
    inFile.close();
    cout<<endl<<"num of deleted : "<<ids.size()<<endl;
    for(int i = 0;i<=ids.size()-1;i++)
    {
        Delete_Account(ids[i]);
    }
}

void search_AC_equal(int balance)
{
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "No data available!";
        return;
        }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "AC NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
    while (inFile.read((char * ) & call, sizeof(Bank)))
        {
       if(call.deposit == balance )
            {
                call.report();
            }
        }
    inFile.close();
}

void search_AC_upper(int balance)
{
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "No data available!";
        return;
        }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "A/C NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
    while (inFile.read((char * ) & call, sizeof(Bank)))
        {
        if(balance <= call.deposit)
            {
                call.report();
            }
        }
    inFile.close();
}

void Get_The_Richest()
{
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
        {
        cout << "No data available!";
        return;
        }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "AC NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
        vector<Bank> n;
    while (inFile.read((char * ) & call, sizeof(Bank)))
        {
            n.push_back(call);
        }
    inFile.close();

    int temp=0;
    Bank high;
    for(int i=0 ; i <= n.size();i++ )
        if(n[i].deposit >= temp)
        {
             temp = n[i].deposit;
             high = n[i];
        }

    high.report();
}

void Deposit_Withdraw(long long n, int option)
{
    int amt;
    Bank call;
    bool found = false;
    fstream File;
    File.open("account.dat", ios::binary | ios:: in | ios::out);
    if (!File)
        {
        cout << "No data available!";
        return;
        }
    while (!File.eof() && found == false)
        {
        File.read((char * ) & call, sizeof(Bank));
        if (call.retAcNo() == n)
        {
            call.Show_account();
            if (option == 1)
            {
                cout << "\n\n===========DEPOSIT TO ACCOUNT===========";
                cout << "\n\nEnter the Amount: ";
                cin >> amt;
//				if (call.retdeposit() + amt >= 1000000)
//				{
//					cout << "Maximum money is 1000000/-\nPlease try again: ";
//					cin >> amt;
//				}
                call.dep(amt);
            }
            if (option == 2)
            {
                cout << "\n\n===========WITHDRAW FROM ACCOUNT===========";
                cout << "\n\nEnter the Amount: ";
                cin >> amt;
                call.draw(amt);
            }
            int pos = (-1) * sizeof(call);
            File.seekp(pos, ios::cur);
            File.write((char * ) & call, sizeof(Bank));
            cout << "\n\nAccount Records Updated Successfully.";
            found = true;
        }
        }
    File.close();
    if (found == false)
        cout << "\n\nAccount Records not Found.";
}


void Account_Modification(unsigned long long n)
{
    Bank call;
    bool found = false;
    fstream File;
    File.open("account.dat", ios::binary | ios:: in | ios::out);
    if (!File)
        {
        cout << "No data available!";
        return;
        }
    while (!File.eof() && found == false)
    {
        File.read((char * ) & call, sizeof(Bank));
        if (call.retAcNo() == n)
        {
            call.Show_account();
            cout << "\n\n===========MODIFY ACCOUNT===========";
            cout << "\nNew Details of the Account: " << endl;
            call.Modification_data();
            int pos = (-1) * sizeof(Bank);
            File.seekp(pos, ios::cur);
            File.write((char * ) & call, sizeof(Bank));
            cout << "\n\nRecord Updated.";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found.";
}

void Credit()
{
    system_clear();
    cout << "\n\nBanking Record System data structure Project in c++" << "\n#Written by amin azad\n";
}


// A recursive function to do inorder traversal
void inorderHelper(Node *root)
{
	if (root == NULL)
		return;

	inorderHelper(root->left);
	inorderHelper(root->right);
}

/* A utility function to insert
   a new node with given key
   in BST */
Node* BSTInsert(Node* root, Node *pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL)
	return pt;

	/* Otherwise, recur down the tree */
	if (pt->data.deposit < root->data.deposit)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->data.deposit > root->data.deposit)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

// Utility function to do level order traversal
void levelOrderHelper(Node *root)
{
	if (root == NULL)
		return;

	std::queue<Node *> q;
	q.push(root);

	while (!q.empty())
	{
		Node *temp = q.front();
		cout << temp->data.deposit << " ";
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);

		if (temp->right != NULL)
			q.push(temp->right);
	}
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violations
// caused by BST insertion
void RBTree::fixViolation(Node *&root, Node *&pt)
{
	Node *parent_pt = NULL;
	Node *grand_parent_pt = NULL;

	while ((pt != root) && (pt->color != BLACK) &&
		(pt->parent->color == RED))
	{

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/* Case : A
			Parent of pt is left child
			of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left)
		{

			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			The uncle of pt is also red
			Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else
			{
				/* Case : 2
				pt is right child of its parent
				Left-rotation required */
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is left child of its parent
				Right-rotation required */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color,
                    grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/* Case : B
		Parent of pt is right child
		of Grand-parent of pt */
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt -> color == RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is right child of its parent
				Left-rotation required */
				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color,
                    grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}

// Function to insert a new node with given data
void RBTree::insert(const Bank &data)
{
	Node *pt = new Node(data);

	// Do a normal BST insert
	root = BSTInsert(root, pt);

	// fix Red Black Tree violations
	fixViolation(root, pt);
}

// Function to do inorder and level order traversals
void RBTree::inorder()	 {inorderHelper(root);}
void RBTree::levelOrder() {levelOrderHelper(root);}


int main()
{
    int choice;
    unsigned long long account_number;
    Bank call;

    Credit();
    do {
        cout << "\n===========================";
        cout << "\n  BANKING RECORD SYSTEM";
        cout << "\n===========================\n";
        cout << "\n\n01. Create New Account";
        cout << "\n\n02. Modify An Account";
        cout << "\n\n03. Balance Enquiry Of An Account";
        cout << "\n\n04. Deposit In An Account";
        cout << "\n\n05. Withdraw From An Account";
        cout << "\n\n06. Close An Account";
        cout << "\n\n07. Balance Equal";
        cout << "\n\n08. Balance Equal and Upper";
        cout << "\n\n09. Get The Richest";
        cout << "\n\n10. Get Negative Accounts Balance";
        cout << "\n\n11. Delete Negative Accounts";
        cout << "\n\n12. Lottery";
        cout << "\n\n13. All Account Holders List";
        cout << "\n\n14. Exit From The Program";
        cout << "\n\nSELECT THE OPTION: ";
        cin >> choice;
        system_clear();

        switch (choice)
        {
        case 1:
            call.Write_Data();
            r.insert(call);
            break;

        case 2:
            cout << "\n\n\tAccount No: ";
            cin >> account_number;
            Account_Modification(account_number);
            break;

        case 3:
            cout << "\n\nAccount No: ";
            cin >> account_number;
            call.Display_Individual_Records(account_number);
            break;

        case 4:
            cout << "\n\nAccount No: ";
            cin >> account_number;
            Deposit_Withdraw(account_number, 1);
            break;

        case 5:
            cout << "\n\nAccount No: ";
            cin >> account_number;
            Deposit_Withdraw(account_number, 2);
            break;

        case 6:
            cout << "\n\nAccount No: ";
            cin >> account_number;
            Delete_Account(account_number);
            break;

        case 7:
            cout<<"Enter The Balance: ";
            int b;
            cin>>b;
            search_AC_equal(b);
            break;

        case 8:
            cout<<"Enter The Balance: ";
            int c;
            cin>>c;
            search_AC_upper(b);
            break;

        case 9:
            Get_The_Richest();
            break;

        case 10:
            Get_minus();
            break;

        case 11:
            Del_minus();
            break;

        case 12:
            Lottery();
            break;

        case 13:
            Get_All_Data();
            break;

        case 14:
            break;

        default:
            cout << "\a";
        }
        cin.clear();
		fflush(stdin);
        cin.get();
        system_clear();
        }
        while (choice != 14);
}
