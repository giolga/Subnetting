#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string findWhat;//quiz1, quiz2
string ip4, findClass;
string subnetMask ,firstAvailableHostAddressofSubnet1, MaxNOfhostsSubnet;
string findSM, partOfSM;
string slash, NA, BA;
int first, second, third, fourth;
long long subnetsRequired, n, ipSize, cntOf255, hostLeft, availableHosts, range;
int afterSlash, bit, period, forSubnett;
int networkAddress, x;

string nTimesOne(int n) {
    int zerosLeft = 8 - n;
    string ans = "";
    while(n > 0) {
        ans += "1";
        n--;
    }

    while (zerosLeft > 0) {
        ans += "0";
        zerosLeft--;
    }

    return ans;
}

string binToDec(string s) {
    int k, x, ans = 0, i;
    string stAns = "";
        k = s.size();
        x = k - 1;
        for(i = 0; i < k; i++) {
            ans += (s[i]-48) * pow(2,x);
            x--;
        }

        stAns = to_string(ans);

        return stAns;
}


int main() {
    cout << "Subnetting Quiz1 : quiz1 \nSubnetting Quiz2 : quiz2 \n";

    cin >> findWhat;

    if(findWhat == "quiz1") {
        cout << "Insert IPv4 address: ";
        cin >> ip4;

        cout << "Insert Subnets required: ";
        cin >> subnetsRequired;

        n = log2(subnetsRequired);

        if(pow(2,n) < subnetsRequired) n++;

        cout << endl << endl << "n-times one for S/M: " << n << endl;
        hostLeft = 8 - n;
        cout << "n-times zero for Hosts: " << hostLeft << endl;
        //octets
        int k = 0;
        ipSize = ip4.size();

        while(ip4[k] != '.') {
            first = first * 10 + ip4[k] - 48;
            k++;
        } k++;

        while (ip4[k] != '.') {
            second = second * 10 + ip4[k] - 48;
            k++;
        } k++;

        while (ip4[k] != '.') {
            third = third * 10 + ip4[k] - 48;
            k++;
        } k++;

        while (k < ipSize) {
            fourth = fourth * 10 + ip4[k]-48;
            k++;
        }

        cout << "Network: " << first << '.' << second << '.' << third << '.' << fourth << endl;
        //find class    A B C

        if(first > 0 && first < 127) {
            // cout << "Class: A\n";
            cntOf255 = 1; 
            findClass = "A";
        }
        else if(first > 127 && first < 192) {
            // cout << "Class: B\n"; 
            cntOf255 = 2; 
            findClass = "B";
        }
        else {
            // cout << "Class: C\n"; 
            cntOf255 = 3; findClass = "C";
        }

        k = 4;//for S/M, if cntOf255=3 then there is one zero left, so k should be equal to 4 for while loop
        k -= cntOf255;

        while (cntOf255 > 0) {
            subnetMask += "255.";
            cntOf255--;
        }

        findSM = nTimesOne(n);
        // cout << "FORSUBNETTTTT: " << findSM << endl;
        partOfSM = binToDec(findSM);
        // cout << partOfSM << endl;
        subnetMask += partOfSM + ".";

        k--;
        while (k > 0) {
            subnetMask += "0.";
            k--;
        }

        subnetMask = subnetMask.substr(0, subnetMask.size() - 1);//silamazistvis
        cout << "\n\n\t Subnet Mask: " << subnetMask << endl;

        //first available host
        range = pow(2,hostLeft);

        if(findClass == "A") {
            firstAvailableHostAddressofSubnet1 = to_string(first) + "." + to_string(range) + "." + to_string(third) + "." + to_string(fourth+1);
        } else if(findClass == "B") {
            firstAvailableHostAddressofSubnet1 = to_string(first) + "." + to_string(second) + "." + to_string(range) + "." + to_string(fourth+1);
        } else {
            firstAvailableHostAddressofSubnet1 = to_string(first) + "." + to_string(second) + "." + to_string(third) + "." + to_string(range+1);
        }
        
        cout << "\t 1st Available Host Address of Subnet 1: " << firstAvailableHostAddressofSubnet1 << endl;

        //number of hosts
        if(findClass == "A") {
            availableHosts = ( 256 - stoi(partOfSM)) * 256 * 256;
        }else if(findClass == "B") {
            availableHosts = ( 256 - stoi(partOfSM)) * 256;
        } else {
            availableHosts = 256 - stoi(partOfSM);
        }

        availableHosts -= 2;    MaxNOfhostsSubnet = to_string(availableHosts);
        cout << "\t Max # of hosts/subnet: " << MaxNOfhostsSubnet << endl;

    } else {

        cout << "Insert IPv4 Address with it's mask (/24): ";
        cin >> ip4 >> slash;
        int k = 0;
        ipSize = ip4.size();

        while(ip4[k] != '.') {
            first = first * 10 + ip4[k] - 48;
            k++;
        } k++;

        while (ip4[k] != '.') {
            second = second * 10 + ip4[k] - 48;
            k++;
        } k++;

        while (ip4[k] != '.') {
            third = third * 10 + ip4[k] - 48;
            k++;
        } k++;

        while (k < ipSize) {
            fourth = fourth * 10 + ip4[k] - 48;
            k++;
        }

        cout << "\n\nAll octets: " << first << '.' << second << '.' << third << '.' << fourth << endl;

        //define slash
        k=1;
        while(k != slash.size()) {
            afterSlash = afterSlash * 10 + slash[k] - 48;
            k++;
        }

        cout << "afterSlash: " << afterSlash << endl;

        if(afterSlash >= 8 && afterSlash < 16) {
            findClass = "A"; 
            cntOf255 = 1; 
            bit = 8;
        }
        else if(afterSlash >= 16 && afterSlash < 24) {
            findClass = "B"; 
            cntOf255 = 2; 
            bit = 16; 
        }
        else {
            findClass = "C"; 
            cntOf255 = 3; 
            bit = 24; 
        }
        
        period = bit + 8 - afterSlash;
        forSubnett = abs(afterSlash - bit);

        cout << "n times one: " << forSubnett << endl;
        cout << "Define Class: " << findClass << endl;
        cout << "Period: " << period << endl;

        findSM = nTimesOne(forSubnett);
        cout<<"Subnett: "<<findSM<<endl;

        //Define network address and broadcast address
        if(findClass == "A") {
            networkAddress = pow(2, period);
             x = networkAddress;
            networkAddress = (second / networkAddress) * networkAddress;
            NA = to_string(first) + "." + to_string(networkAddress) + "." + "0." + "0";
            BA = to_string(first) + "." + to_string(networkAddress + x - 1) + "." + "255." + "255";
        } else if(findClass == "B") {
            networkAddress = pow(2,period);
            x = networkAddress;
            networkAddress = (third / networkAddress) * networkAddress;
            NA = to_string(first) + "." + to_string(second) + "." + to_string(networkAddress) + "." + "0";
            BA = to_string(first) + "." + to_string(second) + "." + to_string(networkAddress + x - 1) + "." + "255";
        } else {
            networkAddress = pow(2,period);
            x = networkAddress;
            networkAddress = (fourth / networkAddress) * networkAddress;
            NA = to_string(first) + "." + to_string(second) + "." + to_string(third) + "."+ to_string(networkAddress);
            BA = BA = to_string(first) + "." + to_string(second) + "." + to_string(third) + "." + to_string(networkAddress + x - 1);
        }

        // cout << "XXX" << x << endl;
        cout << "\n\n\t Network Address: " << NA << endl;
        cout << "\t Broadcast address: " << BA << endl;
        
        //Define subnet mask
        k = 4;//for S/M, if cntOf255=3 then there is one zero left, so k should be equal to 4 for while loop
        k -= cntOf255;
        while(cntOf255 > 0) {
            subnetMask += "255.";
            cntOf255--;
        }

        partOfSM = binToDec(findSM);
        subnetMask += partOfSM + '.';

        k--;
        while(k > 0) {
            subnetMask += "0.";
            k--;
        }

        subnetMask = subnetMask.substr(0, subnetMask.size() - 1);

        cout << "\t Subnet mask: " << subnetMask << endl;
    }

    return 0;
}