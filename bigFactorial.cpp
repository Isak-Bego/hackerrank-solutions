#include <bits/stdc++.h>

string add(string a, string b) {
    int carry = 0;
    string sum = "";
    char* pointer_a = &a[a.length()-1];
    char* pointer_b = &b[b.length()-1];
    int length = max(a.length(), b.length());

    for(int i = 0; i < length; i++) {
        int digit1 = a.length() <= i ? 0 : *pointer_a - '0';
        int digit2 = b.length() <= i ? 0 : *pointer_b - '0';
        int digit_sum = digit1 + digit2 + carry;
        carry = digit_sum / 10;
        sum = i == length-1 ? to_string(digit_sum) + sum : to_string(digit_sum % 10) + sum;
        pointer_a--;
        pointer_b--;
    }

    return sum;
}

string multiply(string a, string b) {
    int carry;
    string sum;
    string product = "";
    char* pointer_a = &a[a.length()-1];
    char* pointer_b = &b[b.length()-1];
    char* temp_pointer1;
    char* temp_pointer2;
    int l1 = min(a.length(), b.length());
    int l2 = max(a.length(), b.length());

    // Suppose that l1 and l2 are not equal
    if(l1 == l2) temp_pointer1 = pointer_a;
    else temp_pointer1 = a.length() == l1 ? pointer_a : pointer_b;

    if (l1 == 1 && l2 == 1) return to_string(stoi(a)*stoi(b));

    for (int i = 0; i < l1; i++) {
        int digit1 = *temp_pointer1 - '0';
        sum = "";
        carry = 0;

        if(l1 == l2) temp_pointer2 = pointer_b;
        else temp_pointer2 = b.length() == l2 ? pointer_b : pointer_a;

        for (int j = 0; j < l2; j++) {
            int digit2 = *temp_pointer2 - '0';
            int digit_product = digit1 * digit2 + carry;
            carry = digit_product / 10;
            sum = j == l2-1 ? to_string(digit_product) + sum : to_string(digit_product % 10) + sum;
            temp_pointer2--;
        }

        for (int k = 0; k < i; k++) {
            sum += "0";
        }

        product = add(product, sum);
        temp_pointer1--;
    }

    return product;
}


int main() {
    int n;
    cout<<"Insert a number in the range 1-200: ";
    cin>>n;
    int temp_n = n;

    string factorial = "1";

    while(n >= 2) {
        factorial = multiply(factorial, to_string(n));
        --n;
    }

    cout<<"The factorial of "<<temp_n<<" is:"<<"\n";
    cout<<factorial;
}