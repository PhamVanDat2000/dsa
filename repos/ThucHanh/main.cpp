/* Note: 
    * You change anything in this answer 
    * such that your implementation must have BusSystem class with method query.
    * This query method should return the output of each instruction
*/
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class BusSystem
{
public:
    class Node
    {
    private:
        string LP;
        int CASE;
        int timeA;
        int timeB;
        Node *next;
        friend class BusSystem;

    public:
        Node(string LP, int CASE, int timeA, int timeB)
        {
            this->LP = LP;
            this->CASE = CASE;
            this->timeA = timeA;
            this->timeB = timeB;
            this->next = nullptr;
        }
        Node() {}
        ~Node() {}
    };

public:
    int N;
    Node **ptr;
    int count = 0;
    BusSystem()
    {
        N = 0;
        ptr = new Node *[1000];
    }

public:
    string query(string instruction)
    {
        // TODO: Your implementation
        int CODE;
        string LP;
        int CASE;
        int timeA, timeB;
        //chuyen chuoi thanh mang
        int size_ = instruction.size();
        char arr[size_];
        strcpy(arr, instruction.c_str());
        //kiem tra cu phap
        if (arr[0] == ' ' || arr[size_ - 1] == ' ')
            return "-1";
        for (int i = 1; i < size_; i++)
        {
            if (arr[i - 1] == ' ' && arr[i] == ' ')
                return "-1";
        }
        string request = "";
        int i = 0;
        while (arr[i] != ' ' && *arr != '\0')
        {
            request += arr[i];
            i++;
        }
        i++;
        // Chia 3 truong hop

        if (request == "SQ")
        {
            string command_1;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_1 += arr[i];
                i++;
            }
            if (command_1.length() == 0)
                return "-1";
            N = atoi(command_1.c_str());
            if (i < size_)
                return "-1";
            //linkedList
            return "1";
        }
        else if (request == "INS")
        {
            if (count >= N)
                return "-1";
            string command_1;
            string command_2;
            string command_3;
            string command_4;
            string command_5;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_1 += arr[i];
                i++;
            }
            i++;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                command_2 += arr[i];
                i++;
            }
            i++;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_3 += arr[i];
                i++;
            }
            i++;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_4 += arr[i];
                i++;
            }
            i++;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_5 += arr[i];
                i++;
            }

            if (command_1.length() == 0 || command_2.length() == 0 || command_3.length() == 0 || command_4.length() == 0)
                return "-1";
            if (command_5.length() != 0)
            {
                CODE = atoi(command_1.c_str());
                LP = command_2;
                CASE = atoi(command_3.c_str());
                timeA = atoi(command_4.c_str());
                timeB = atoi(command_5.c_str());
            }
            else
            {
                CODE = atoi(command_1.c_str());
                LP = command_2;
                CASE = 0;
                timeA = atoi(command_3.c_str());
                timeB = atoi(command_4.c_str());
            }
            if (i < size_)
                return "-1";
            //linked list
            //insert
            Node *pNew = new Node(LP, CASE, timeA, timeB);
            if (count == 0)
            {
                ptr[CODE] = pNew;
                count++;
                return to_string(count);
            }
            else
            {
                Node *p = ptr[CODE];
                Node *pCur = ptr[CODE];
                while (pCur != nullptr)
                {
                    if ((p->timeA == timeA && p->CASE == CASE) || (p->LP == LP && ((p->timeB >= timeA && p->timeA < timeB) || (p->timeB < timeA && p->timeA >= timeB))))
                        return "-1";
                    p = pCur;
                    pCur = pCur->next;
                }
                p->next = pNew;
                count++;
                return to_string(count);
            }
        }
        else if (request == "DEL")
        {
            if (count >= N)
                return "-1";
            string command_1;
            string command_2;
            string command_3;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_1 += arr[i];
                i++;
            }
            i++;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_2 += arr[i];
                i++;
            }
            i++;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_3 += arr[i];
                i++;
            }
            if (command_1.length() == 0)
                return "-1";
            CODE = atoi(command_1.c_str());
            timeA = atoi(command_2.c_str());
            timeB = atoi(command_3.c_str());
            if (i < size_)
                return "-1";
            //linked list
            Node *p = ptr[CODE];
            int del = 0;
            if (command_3.length() != 0 && command_2.length() != 0)
            {
                if (count == 0)
                    return "-1";
                if (p->timeA > timeA && p->timeA < timeB)
                {
                    del++;
                    ptr[CODE] = ptr[CODE]->next;
                    delete p;
                    count--;
                }
                Node *pDel = p->next;
                while (pDel != nullptr)
                {
                    if (pDel->timeA > timeA && pDel->timeA < timeB)
                    {
                        del++;
                        p->next = pDel->next;
                        delete pDel;
                        count--;
                    }
                    else
                    {
                        p = p->next;
                    }
                    pDel = p->next;
                }
                return to_string(del);
            }
            if (command_3.length() == 0 && command_2.length() != 0)
            {
                if (count == 0)
                    return "0";
                if (p->timeA == timeA)
                {
                    del++;
                    ptr[CODE] = ptr[CODE]->next;
                    delete p;
                    count--;
                }
                Node *pDel = p->next;
                while (pDel != nullptr)
                {
                    if (pDel->timeA == timeA)
                    {
                        del++;
                        p->next = pDel->next;
                        delete pDel;
                        count--;
                    }
                    else
                    {
                        p = p->next;
                    }
                    pDel = p->next;
                }
                return to_string(del);
            }
            if (command_3.length() == 0 && command_2.length() != 0)
            {
                if (count != 0)
                {
                    while (count)
                    {
                        Node *p = ptr[CODE];
                        ptr[CODE] = ptr[CODE]->next;
                        delete p;
                        count--;
                    }
                }
            }
        }
        else if (request == "CS" || request == "CE" || request == "GS" || request == "GE")
        {
            if (count >= N)
                return "-1";
            string command_1;
            string command_2;
            string command_3;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_1 += arr[i];
                i++;
            }
            i++;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_2 += arr[i];
                i++;
            }
            i++;
            while (i < size_ && arr[i] != ' ' && *arr != '\0')
            {
                if (arr[i] < 48 || arr[i] > 57)
                    return "-1";
                command_3 += arr[i];
                i++;
            }
            //check đk
            if (command_1.length() == 0 || command_2.length() == 0)
                return "-1";
            CODE = atoi(command_1.c_str());
            timeA = atoi(command_2.c_str());
            CASE = atoi(command_3.c_str());

            if (i < size_)
                return "-1";
            //linked list

            if (request == "CS")
            {
                int numb = 0;
                Node *p = ptr[CODE];
                if (command_3.length() == 0) // k co CASE
                {
                    while (p != nullptr)
                    {
                        if (p->timeA <= timeA && p->timeB >= timeA)
                            numb++;
                        p = p->next;
                    }
                    return to_string(numb);
                }
                else
                {
                    while (p != nullptr)
                    {
                        if (p->timeA <= timeA && p->timeB > timeA && p->CASE == CASE)
                            numb++;
                        p = p->next;
                    }
                    return to_string(numb);
                }
            }
            if (request == "CE")
            {
                int numb = 0;
                Node *p = ptr[CODE];
                if (command_3.length() == 0) // k co CASE
                {
                    while (p != nullptr)
                    {
                        if (p->timeB < timeA)
                            numb++;
                        p = p->next;
                    }
                    return to_string(numb);
                }
                else
                {
                    while (p != nullptr)
                    {
                        if (p->timeB <= timeA && p->CASE == CASE)
                            numb++;
                        p = p->next;
                    }
                    return to_string(numb);
                }
            }
            if (request == "GS")
            {
                string bks = ptr[CODE]->LP;
                int time_res = timeA - ptr[CODE]->timeA;
                Node *p = ptr[CODE]->next;
                if (command_3.length() == 0) // khong co CASE
                {
                    while (p != nullptr && p->timeA < timeA)
                    {
                        if (time_res <= 0)
                        {
                            time_res = timeA - p->timeA;
                        }
                        if (time_res > (timeA - p->timeA))
                        {
                            time_res = timeA - p->timeA;
                            bks = p->LP;
                        }
                        if (time_res == (timeA - p->timeA) && p->CASE == 0)
                        {
                            time_res = timeA - p->timeA;
                            bks = p->LP;
                        }
                        p = p->next;
                    }
                    if (time_res <= 0)
                        return "-1";
                    return bks;
                }
                else // co CASE
                {
                    if (ptr[CODE]->CASE == CASE)
                        bks = ptr[CODE]->LP;
                    else
                    {
                        bks = "-1";
                        time_res = -1;
                    }
                    while (p != nullptr && p->timeA < timeA && p->CASE == CASE)
                    {
                        if (time_res <= 0)
                        {
                            time_res = timeA - p->timeA;
                        }
                        if (time_res > (timeA - p->timeA))
                        {
                            time_res = timeA - p->timeA;
                            bks = p->LP;
                        }
                        if (time_res == (timeA - p->timeA) && p->CASE == 0)
                        {
                            time_res = timeA - p->timeA;
                            bks = p->LP;
                        }
                        p = p->next;
                    }
                    if (time_res <= 0)
                        return "-1";
                    return bks;
                }
            }
            if (request == "GE")
            {
                bool case_0 = false;
                string bks = ptr[CODE]->LP;
                int time_res = timeA - ptr[CODE]->timeB;
                Node *p = ptr[CODE]->next;
                if (command_3.length() == 0) // khong co CASE
                {
                    if (ptr[CODE]->CASE == CASE)
                    {
                        case_0 = true;
                    }
                    while (p != nullptr && p->timeB < timeA)
                    {
                        if (time_res <= 0)
                        {
                            time_res = timeA - p->timeB;
                        }
                        if (time_res > (timeA - p->timeB) || (time_res == (timeA - p->timeB) && p->CASE == 0 && case_0 == false))
                        {
                            time_res = timeA - p->timeB;
                            bks = p->LP;
                        }
                        p = p->next;
                    }
                    if (time_res <= 0)
                        return "-1";
                    return bks;
                }
                else // co CASE
                {
                    if (ptr[CODE]->CASE == CASE)
                    {
                        bks = ptr[CODE]->LP;
                    }
                    else
                    {
                        bks = "-1";
                        time_res = -1;
                    }
                    while (p != nullptr && p->timeB < timeA && p->CASE == CASE)
                    {
                        if (time_res <= 0)
                        {
                            time_res = timeA - p->timeB;
                        }
                        if (time_res > (timeA - p->timeB) || (time_res == (timeA - p->timeB) && p->CASE == 0))
                        {
                            time_res = timeA - p->timeB;
                            bks = p->LP;
                        }
                        p = p->next;
                    }
                    if (time_res <= 0)
                        return "-1";
                    return bks;
                }
            }
        }
        else
            return "-1";
        return "-1";
    }
};
int main()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 3") << endl;
    cout << bs->query("INS 50 50D1-23341 1 5 10") << endl;
    cout << bs->query("INS 50 50D1-23342 1 8 9") << endl;
    cout << bs->query("INS 50 50D1-23342 1 20 22") << endl;
    cout << bs->query("INS 50 50D1-23342 1 29 40") << endl;
    return 0;
}