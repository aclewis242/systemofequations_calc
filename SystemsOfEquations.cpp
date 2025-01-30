#include "SystemsOfEquations.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

SystemsOfEquations::SystemsOfEquations(){
    cout << "For help, please enter the word 'help.' Otherwise, enter something else." << endl;
    string plshelp = "";
    cin >> plshelp;
    if(plshelp=="help"){
        this->help();
    }
    cout << "How many equations would you like?" << endl;
    int inp = 0;
    cin >> inp;
    this->numOfEqs = inp;
    this->equations = {};
    this->eqsUnparsed = {};
    this->singEqUnparsed = {};
    this->varsUsed = {};
    this->mat = {};
    this->matFunc = {};
    this->matNum = {};
    this->post = {};
    this->postFunc = {};
    this->postEqs = {};
    this->augMat = {};
    this->solns = {};
    this->parse = new mainCalc();
    for(int i = 0; i < inp; i++){
        equations.push_back({""});
    }
    this->debug = fstream("debug.txt", fstream::out);
    string inpFixer = "";
    getline(cin, inpFixer);
    debug << "Empty parsed equations vector created with size " << equations.size() << "." << endl;
    for(int i = 0; i < inp; i++){
        string input = "";
        cout << "Please enter equation number " << i+1 << "." << endl;
        getline(cin, input);
        eqsUnparsed.push_back(input);
    }
    cout << "What variables did you use? Please enter them with the syntax of x, y, z." << endl;
    string vars = "";
    getline(cin, vars);
    for(int i = 0; i < vars.size(); i++){
    	if(vars.at(i)!=',' && vars.at(i)!=' '){
    		varsUsed.push_back(vars.at(i));
    		singEqUnparsed.push_back({});
    	}
    }
    for(int i = 0; i < numOfEqs; i++){
    	mat.push_back({});
        matNum.push_back({});
        augMat.push_back({});
        postEqs.push_back({0});
        post.push_back({});
        solns.push_back(0);
    }
    for(int i = 0; i < numOfEqs; i++){
        for(int j = 0; j < numOfEqs; j++){
    	    mat.at(i).push_back({});
            matNum.at(i).push_back({});
        }
    }
    for(int i = 0; i < numOfEqs; i++){
    	for(int j = 0; j < numOfEqs+1; j++){
    		augMat.at(i).push_back({});
    	}
    }
    debug << "Matrix dimensions: " << mat.size() << "x" << mat.at(0).size() << endl;
    debug << "Empty unparsed equations vector created with size " << eqsUnparsed.size() << "." << endl;
    debug << "Iterating through and displaying unparsed equations." << endl;
    for(unsigned int i = 0; i < eqsUnparsed.size(); i++){
        debug << "Equation at index " << i << ": " << eqsUnparsed.at(i) << endl;
    }
    this->parseEquations();
    this->getSolns();
}

void SystemsOfEquations::parseEquations(){
    debug << "\nParsing equations.\n" << endl;
    debug << "Iterating through unparsed equations vector." << endl;
    int eqOn = 0;
    for(string str:eqsUnparsed){
        debug << "\nUnparsed equation being processed: " << str <<"\n"<< endl;
        string toAdd = "";
        debug << "Searching for negative signs." << endl;
        for(int i = 0; i < str.size(); i++){
        	if(str.at(i)!=' '){
        		if(str.at(i)=='-'&&i!=0&&str.at(i-2)!='='){
        			toAdd+="+-";
                    debug << "Found negative sign at index " << i << ", replacing with +-." << endl;
        		}else{
        			toAdd+=str.at(i);
        		}
        	}
        }
        debug << "Equation without spaces and isolated subtraction signs: " << toAdd << endl;
        debug << "\nSearching for coefficient-less variables." << endl;
        for(int i = 0; i < toAdd.size(); i++){
        	for(int j = 0; j < varsUsed.size(); j++){
        		if(toAdd.at(i)==varsUsed.at(j)){
                    debug << "Variable " << toAdd.at(i) << " found at index " << i << "." << endl;
                    if(i==0){
                        debug << "Entered i is zero if statement." << endl;
                        toAdd.insert(i,"1");
                        i++;
                        debug << "Variable was found to be coefficient-less, so 1 has been supplied." << endl;
                    }else if((i!=0)&&((toAdd.at(i-1)=='+'&&toAdd.at(i)!='-')||toAdd.at(i-1)=='-')||toAdd.at(i-1)=='='){
                        debug << "Entered i is not zero if statement." << endl;
        				toAdd.insert(i,"1");
                        i++;
                        debug << "Variable was found to be coefficient-less, so 1 has been supplied." << endl;
        			}else{
                        debug << "Has coefficient, and so nothing shall be done." << endl;
                    }
        		}
        	}
        }
        debug << "Equation without coefficient-less variables: " << toAdd << endl;
        int eqInd = 0;
        debug << "\nSearching for equals sign." << endl;
        for(int i = 0; i < toAdd.size(); i++){
           	if(toAdd.at(i)=='='){
          		eqInd = i;
                debug << "Equals sign found at index " << i << "." << endl;
           	}
        }
        string preEq = "";
        string postEq = "";
        for(int i = 0; i < eqInd; i++){
        	preEq+=toAdd.at(i);
        }
        debug << "Pre-equals sign equation: " << preEq << endl;
        for(int i = eqInd+1; i < toAdd.size(); i++){
        	postEq+=toAdd.at(i);
        }
        debug << "Post-equals sign equation: " << postEq << endl;
    	vector<string> stuffToAdd = {};
    	int sinceLastVar = 1;
    	int stored = 0;
    	post.at(eqOn).push_back(postEq);
        debug << "Making vector for coefficients." << endl;
        for(int i = 0; i < preEq.size(); i++){
        	for(int j = 0; j < varsUsed.size(); j++){
        		if(preEq.at(i)==varsUsed.at(j)){
        			debug << "Variable " << varsUsed.at(j) << " found at index " << i << "." << endl;
        			for(int k = stored; k < sinceLastVar; k++){
        				if(preEq.at(k)!='+'){
        					singEqUnparsed.at(j).push_back(preEq.at(k));
        					debug << "Character " << preEq.at(k) << " pushed to back of equation for variable " << varsUsed.at(j) << "." << endl;
        				}
        			}
        			stored = sinceLastVar;
        		}
        	}
        	sinceLastVar++;
        }
        debug << "Exited variable splitter." << endl;
        for(int i = 0; i < numOfEqs; i++){
        	debug << "Statement for variable " << varsUsed.at(i) << ": ";
        	for(int j = 0; j < singEqUnparsed.at(i).size(); j++){
        		debug << singEqUnparsed.at(i).at(j);
        		//mat.at(i).at(j).push_back(singEqUnparsed.at(i).at(j));
        	}
        	debug << endl;
        }
        vector<string> eqs = {};
        for(int i = 0; i < numOfEqs; i++){
        	eqs.push_back("");
        }
        for(int i = 0; i < singEqUnparsed.size(); i++){
        	for(int j = 0; j < singEqUnparsed.at(i).size(); j++){
        		eqs.at(i)+=singEqUnparsed.at(i).at(j);
        	}
        }
        for(int i = 0; i < eqs.size(); i++){
        	mat.at(eqOn).at(i) = eqs.at(i);
        }
        debug << "Current matrix: " << endl;
        printMatrix(mat);
        singEqUnparsed = {};
        for(int i = 0; i < numOfEqs; i++){
        	singEqUnparsed.push_back({});
        }
        eqOn++;
    }
    debug << "Removing variables from matrix." << endl;
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat.at(i).size(); j++){
        	debug << "Variable at position " << i << "," << j << " " << mat.at(i).at(j).at(mat.at(i).at(j).size()-1) << " removed." << endl;
            mat.at(i).at(j) = mat.at(i).at(j).substr(0, mat.at(i).at(j).size()-1);
        }
    }
    debug << "Matrix without variables: " << endl;
    printMatrix(mat);
    debug << "Coefficient matrix: " << endl;
    printMatrix(post);
    matFunc = mat;
    postFunc = post;
    debug << "Checking for functions." << endl;
    /*for(int i = 0; i < mat.size(); i++){
    	for(int j = 0; j < mat.at(i).size(); j++){
    		for(int c = 0; c < mat.at(i).at(j).size()-1; c++){
    			if((mat.at(i).at(j).at(c)>=97&&mat.at(i).at(j).at(c)<=122)&&(mat.at(i).at(j).at(c+1)<97||mat.at(i).at(j).at(c+1)>122)){
    				matFunc.at(i).at(j).insert(c+1, " ");
    			}
    		}
    	}
    }*/
    for(int i = 0; i < mat.size(); i++){
    	for(int j = 0; j < mat.at(i).size(); j++){
    		for(int k = 0; k < mat.at(i).at(j).size(); k++){
    			if(mat.at(i).at(j).at(k)=='(' || mat.at(i).at(j).at(k)==')'){
    				matFunc.at(i).at(j).at(k) = ' ';
    				debug << "Character next to number found at position " << i << "," << j << ", index " << k << ", value " << mat.at(i).at(j).at(k) << "; inserting space after." << endl;
    			}
    		}
    	}
    }
    debug << "Checking for negative signs." << endl;
    for(int i = 0; i < matFunc.size(); i++){
    	for(int j = 0; j < matFunc.at(i).size(); j++){
    		for(int c = 0; c < matFunc.at(i).at(j).size()-1; c++){
    			if(matFunc.at(i).at(j).at(c)=='-'){
    				matFunc.at(i).at(j).insert(c+1, " ");
    				debug << "Negative sign found at position " << i << "," << j << ", index " << c << "; inserting space after." << endl;
    			}
    		}
    	}
    }
    debug << "Checking for functions in the coefficient matrix." << endl;
    /*for(int i = 0; i < post.size(); i++){
    	for(int j = 0; j < post.at(i).size(); j++){
    		for(int c = 0; c < post.at(i).at(j).size()-1; c++){
    			if((post.at(i).at(j).at(c)>=97&&post.at(i).at(j).at(c)<=122)&&(post.at(i).at(j).at(c+1)<97||post.at(i).at(j).at(c+1)>122)){
    				postFunc.at(i).at(j).insert(c+1, " ");
    				debug << "Character next to number found at position " << i << "," << j << ", index " << c << ", value " << mat.at(i).at(j).at(c) << "; inserting space after." << endl;
    			}
    		}
    	}
    }*/
    for(int i = 0; i < post.size(); i++){
    	for(int j = 0; j < post.at(i).size(); j++){
    		for(int k = 0; k < post.at(i).at(j).size(); k++){
    			if(post.at(i).at(j).at(k)=='(' || post.at(i).at(j).at(k)==')'){
    				postFunc.at(i).at(j).at(k) = ' ';
    				debug << "Character next to number found at position " << i << "," << j << ", index " << k << ", value " << post.at(i).at(j).at(k) << "; inserting space after." << endl;
    			}
    		}
    	}
    }
    debug << "Checking for negative signs in the coefficient matrix." << endl;
    for(int i = 0; i < postFunc.size(); i++){
    	for(int j = 0; j < postFunc.at(i).size(); j++){
    		for(int c = 0; c < postFunc.at(i).at(j).size()-1; c++){
    			if(postFunc.at(i).at(j).at(c)=='-'){
    				postFunc.at(i).at(j).insert(c+1, " ");
    				debug << "Negative sign found at position " << i << "," << j << ", index " << c << "; inserting space after." << endl;
    			}
    		}
    	}
    }
    debug << "Current matrix: " << endl;
    printMatrix(matFunc);
    debug << "Current coefficient matrix: " << endl;
    printMatrix(postFunc);
    debug << "Converting string matrix into a double matrix." << endl;
    for(int i = 0; i < matNum.size(); i++){
        for(int j = 0; j < matNum.at(i).size(); j++){
            matNum.at(i).at(j) = parse->returnAns(matFunc.at(i).at(j));
        }
    }
    debug << "Converting coefficient string matrix into a double matrix." << endl;
    debug << "Dimensions of postEqs matrix: " << postEqs.size() << "x" << postEqs.at(0).size() << endl;
    debug << "Dimensions of postFunc matrix: " << postFunc.size() << "x" << postFunc.at(0).size() << endl;
    for(int i = 0; i < postEqs.size(); i++){
    	for(int j = 0; j < postEqs.at(i).size(); j++){
    		postEqs.at(i).at(j) = parse->returnAns(postFunc.at(i).at(j));
    	}
    }
    debug << "Matrix converted into doubles: " << endl;
    printMatrix(matNum);
    debug << "Coefficient matrix converted into doubles: " << endl;
    printMatrix(postEqs);
    debug << "Beginning Gauss-Jordan elimination." << endl;
    debug << "Combining matrices into an augmented matrix." << endl;
    for(int i = 0; i < matNum.size(); i++){
    	for(int j = 0; j < matNum.at(i).size(); j++){
    		augMat.at(i).at(j) = matNum.at(i).at(j);
    	}
    }
    for(int i = 0; i < postEqs.size(); i++){
    	for(int j = 0; j < postEqs.at(i).size(); j++){
    		augMat.at(i).at(matNum.size()+j) = postEqs.at(i).at(j);
    	}
    }
    debug << "Augmented matrix: " << endl;
    printMatrix(augMat);
    double temp = 0;
    for(int i = 0; i < matNum.size(); i++){
    	for(int j = 0; j < matNum.size(); j++){
    		if(i!=j){
    			temp = augMat.at(j).at(i)/augMat.at(i).at(i);
    			for(int k = 0; k < matNum.size()+1; k++){
    				augMat.at(j).at(k) = augMat.at(j).at(k) - temp*augMat.at(i).at(k);
    			}
    		}
    	}
    }
    debug << "Matrix in diagonal form:" << endl;
    printMatrix(augMat);
    debug << "Calculating solutions from matrix." << endl;
    for(int i = 0; i < matNum.size(); i++){
    	solns.at(i) = augMat.at(i).at(matNum.size())/augMat.at(i).at(i);
    }
    debug << "Solutions:" << endl;
    for(int i = 0; i < solns.size(); i++){
    	debug << varsUsed.at(i) << " = " << solns.at(i) << endl;
    }
}

void SystemsOfEquations::getSolns(){
	debug << "Printing solutions." << endl;
	for(int i = 0; i < solns.size(); i++){
		cout << varsUsed.at(i) << " = " << solns.at(i) << endl;
	}
}

void SystemsOfEquations::help(){
    cout << "This program does not support non-linear expressions; namely, no functions of variables (e.g. \"x^2\"), though functions of constants (e.g. \"2^2\") are fine." << endl;
    cout << "Variables may only be one letter in length." << endl;
    cout << "When entering equations, please ensure that there is only one instance of each variable, where all variable terms are on the left and all constants are on the right." << endl;
    cout << "Please ensure that all terms have spaces between them (i.e., 2x + y = 3 instead of 2x+y=3)." << endl;
	cout << "Coefficients must be directly adjacent to their corresponding variables. For instance, 'sin(30)x' is correct, while 'sin(30)*x' is not." << endl;
    cout << "Most common mathematical functions (sin, cos, etc.) are supported. For a full list, please enter 's'." << endl;
    string s = "";
    cin >> s;
    if(s=="s"){
        cout << "Supported functions: \n+\n-\n*\n/\n^\nlog\nln\nsin\ncos\ntan\narcsin\narccos\narctan" << endl;
        cout << "csc\nsec\ncot\narccsc\narcsec\narccot\nsinh\ncosh\ntanh\ncsch\nsech\ncoth\n" << endl;
		cout << "Note that all trigonometric functions assume/return an input in degrees.\n" << endl;
    }
}

void SystemsOfEquations::printMatrix(vector<vector<string>> m){
    for(int i = 0; i < m.size(); i++){
       	for(int j = 0; j < m.at(i).size(); j++){
       		debug << m.at(i).at(j) << " ";
       	}
       	debug << endl;
    }
}

void SystemsOfEquations::printMatrix(vector<vector<double>> m){
    for(int i = 0; i < m.size(); i++){
       	for(int j = 0; j < m.at(i).size(); j++){
       		debug << m.at(i).at(j) << " ";
       	}
       	debug << endl;
    }
}