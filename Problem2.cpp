#include <iostream>
#include <fstream>
using namespace std;

class Polynomial
{
    int order;
    int* coefficients;
    int firstNONzero;
    int lastNONzero;
    void findFirstAndLastNONzero()
    {
        firstNONzero = -1;
        lastNONzero = -1;
        for(int i=1; i<=order+1;i++)
        {
            if(coefficients[i] != 0)
            {
                if(firstNONzero == -1)
                    firstNONzero = i;
                lastNONzero = i;
            }
        }
    }
public:

    string display()
    {
        //find the index of the first and last non-zero elements
        findFirstAndLastNONzero();
        string result = "";
        //process all the terms in the polynomial, starting from the highest order term to the first constant term
        for(int i=order+1; i>=1;i--)
        {
            //skip terms that have a zero coefficient
            if(coefficients[i] == 0)
                continue;

            // Add sign only if it's not the first nonzero term
            if (i != lastNONzero)
                result += (coefficients[i] < 0) ? "- " : "+ ";

            else
            {
                // However, if it's the first nonzero term and negative, add the minus sign
                if(coefficients[i] < 0)
                {
                    result += "-";
                }
            }

            //If this is the constant term
            if(i==1)
            {
                //Add its coefficient only
                result += to_string(abs(coefficients[i]));

            }
                //If this is the linear term
            else if (i == 2)
            {
                //Only add the coefficient if it isn't either 1 or -1
                if(!(coefficients[i] == 1 || coefficients[i] == -1))
                {
                    result += to_string(abs(coefficients[i]));
                }
                //add x to the one (without showing the exponentiation)
                result += "x";
            }
            else
                //For an arbitrary term
            {
                //Only add the coefficient if it isn't 1 or -1
                if(!(coefficients[i] == 1 || coefficients[i] == -1))
                {
                    result += to_string(abs(coefficients[i]));
                }
                //add the arbitrary power of x
                result += "x^";
                result += to_string(i-1);
            }
            //add a space after processing the term
            result += " ";

            //add the "=" sign after the first non-zero term, followed by the value of the second constant term
            if(i == firstNONzero)
            {
                result += "= ";
                result += to_string(coefficients[0]);
            }

        }

        return result;
    }
    Polynomial add(const Polynomial& addendum)
    {
        //The result's order should be of the same order as the polynomial with the highest order
        int resultOrder = max(order, addendum.order);
        Polynomial result(resultOrder);
        for(int i = 0; i < resultOrder+2; i++)
        {
            int coeff1 = (this->order+1 < i) ? 0 : this->coefficients[i]; //If we exceeded the order of our polynomial, let its contrubution to the result's coefficient be zero
            int coeff2 = (addendum.order+1 < i) ? 0 : addendum.coefficients[i]; //Do the same with the addendum polynomial
            result.coefficients[i] = coeff1 + coeff2; //Add the contribution of both my polynomial and the added polynomial to the result
        }
        return result;
    }

    Polynomial subtract(const Polynomial& subtrahend)
    {
        int resultOrder=0;
        //If the order of my polynomial is the same as the subtrahend, the order of the result should be the first index in which the differenec between my poly. coeff and the subtrahend's coeff. is non-zero (moving descendingly)
        if(this->order == subtrahend.order)
        {
            for(int j=this->order+1; j>=0;j--)
            {
                if(this->coefficients[j] - subtrahend.coefficients[j] != 0)
                {
                    resultOrder = j-1;
                    break;
                }
            }
        }
            //else, it would be of the same order as the polynomial with the highest order
        else
        {
            resultOrder = max(this->order, subtrahend.order);
        }

        Polynomial result(resultOrder);
        //The same logic used with the add method
        for(int i = 0; i < resultOrder+2; i++)
        {
            int coeff1 = (this->order+1 < i) ? 0 : this->coefficients[i];
            int coeff2 = (subtrahend.order+1 < i) ? 0 : subtrahend.coefficients[i];
            result.coefficients[i] = coeff1 - coeff2;
        }
        return result;
    }
    Polynomial(int order=0, int* coefficients=0)
    {
        this->order = order;
        this->coefficients = new int[order + 2];
        if (coefficients==0) //If an array of coefficients was not passed, initialize all the coefficients to 0
        {
            for (int i = 0; i < order + 2; i++) {
                this->coefficients[i] = 0;
            }
        }
        else //else, copy the elements in the passed coefficients array to the polynomial's coefficients array
        {
            for (int i = 0; i < order + 2; i++)
            {
                setCoefficient(coefficients[i],i);
            }
        }
    }
    void setCoefficient(int coefficient, int index) //sets a passed number as some coefficient of the polynomial at a given index
    {
        coefficients[index] = coefficient;
    }
    void setAllCoefficients(ifstream &file) //sets all the coefficients according to a passed file
    {
        int coeff;
        for(int i=0; i<order+2;i++)
        {
            if(!(file >> coeff)) //if no number was read from the file and we still didn't input all the coefficients
            {
                cout << "You need to input more coefficients"<<endl;
                break;
            }
            setCoefficient(coeff, i);
        }
    }
    ~Polynomial()
    {
        delete [] coefficients;
        coefficients=0;
    }
};

int main()
{
    cout << "The following are test cases for the polynomial class (assuming the order is 3): "<<endl<<endl;
    ifstream testFile("C:/Users/Asser/CLionProjects/DSAssignment2/testFile.txt");
    if(!testFile)
    {
        cout << "Error: something wrong occured while trying to open the test cases file" << endl;
    }
    else
    {

        Polynomial test(3);
        //initiate all the tests
        //All negative coefficients
        cout << "In case the input had all negative coefficients; "<<endl;
        test.setAllCoefficients(testFile);
        cout<<"The polynomial would be: "<<endl;
        cout<<test.display()<<endl<<endl;

        //All positive coefficients
        cout << "In case the input had all positive coefficients; "<<endl;
        test.setAllCoefficients(testFile);
        cout<<"The polynomial would be: "<<endl;
        cout<<test.display()<<endl<<endl;

        //Some zero coefficients
        cout << "In case the input had some zero coefficients; "<<endl;
        test.setAllCoefficients(testFile);
        cout<<"The polynomial would be: "<<endl;
        cout<<test.display()<<endl<<endl;

        //All the coefficients were 1
        cout << "In case the input had coefficients that were all 1; "<<endl;
        test.setAllCoefficients(testFile);
        cout<<"The polynomial would be: "<<endl;
        cout<<test.display()<<endl<<endl;

        Polynomial test2(3);
    }
    cout << "We'll now perform all the operations there is on the 2 polynomials that were constructed by the input you provided in the \"inputFile.txt\" file"<<endl<<endl;

    ifstream inputFile("C:/Users/Asser/CLionProjects/DSAssignment2/inputFile.txt");
    int firstOrder; inputFile >> firstOrder;
    cout<<"Order of first polynomial: "<<firstOrder<<endl;
    Polynomial p1(firstOrder);
    cout<<"Enter polynomial: ";
    int coeff;
    for(int i=0; i<firstOrder+2; i++)
    {
        inputFile>>coeff;
        p1.setCoefficient(coeff, i);
        cout<<coeff<< " ";
    }
    cout<<endl<<endl;

    int secondOrder; inputFile >> secondOrder;
    cout<<"Order of second polynomial: "<<secondOrder<<endl;
    Polynomial p2(secondOrder);
    cout<<"Enter polynomial: ";
    for(int i=0; i<secondOrder+2; i++)
    {
        inputFile>>coeff;
        p2.setCoefficient(coeff, i);
        cout<<coeff<< " ";
    }
    cout<<endl<<endl;

    cout<< "First Polynomial: " << p1.display() <<endl;
    cout<< "Second Polynomial: " << p2.display() <<endl;
    cout<< "Sum of polynomials: " << (p1.add(p2)).display() <<endl;
    cout<< "Difference of polynomials: " << (p2.subtract(p1)).display() <<endl;
    return 0;
}
