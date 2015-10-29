#include "tests.h"

using namespace std;

//Temporary simple alphabet
static const char alphanum[] =
	/*"0123456789"
	"!@#$%^&*"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";*/
	"ACTG";

int stringLength = sizeof(alphanum) - 1;

// Random string generator function.
char genRandom()
{

    return alphanum[rand() % stringLength];
}

int getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int getMilliSpan(int nTimeStart){
	int nSpan = getMilliCount() - nTimeStart;
	if(nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

int main() {
	const int patLens = 4;
	const int patsPerLen = 1;
	const int editCount = 2;
	int targetsCount = 3;
	string editDistances[editCount] = {"0", "1"};
	string randomPatterns[patLens][targetsCount]; //500 de cada tamanho, 12, indo de 2 até 4096
	

	printf("\nGenerating patterns (%d pattern(s) per length, lenght(s) from 2 to 2^%d)...\n", patsPerLen, patLens);

	int i, j, k;
	int patLen = 2;
	for (i = 0; i < patLens; i++)	{
		for (j = 0; j < targetsCount;j++) {
			for (k = 0; k < patLen; k++) {
				randomPatterns[i][j] += genRandom();
			}
		}
		patLen *= 2;
	}

	string targets[3] = {"data/dna.50MB", "data/dna.100MB", "data/dna.200MB"};

	int pmtExecTimes[patLens][targetsCount]; 					// pmt exato com boyer moore com 1 padrão
	int pmtKMPExecTimes[patLens][targetsCount]; 				// pmt exato com kmp com 1 padrão
	int grepExecTimes[patLens][targetsCount];					// grep com 1 padrão
	int pmtApproxExecTimes[patLens][targetsCount][editCount];	// pmt aproximado com sellers com 1 padrão
	int agrepExecTimes[patLens][targetsCount][editCount];		// agrep com 1 padrão

	int start;

	printf("Searching...\n");
	int target;
	for (target = 0; target < targetsCount; target++)
	{
		printf("Target %s\n", targets[target].c_str());
	
		for (i = 0; i < patLens; i++)	{
			printf("Patterns with length 2^%d...\n", (i+1));

				//Executar pmt com um padrão
				//cout << (("bin/pmt -q '"+randomPatterns[i][j]+"' "+targets[target]).c_str()) << endl;
				start = getMilliCount();
				system (("bin/pmt -q '"+randomPatterns[i][target]+"' "+targets[target]).c_str());
				pmtExecTimes[i][target] = getMilliSpan(start);//difftime( time(0), start); //(double)(clock() - tStart)/CLOCKS_PER_SEC;
				//cout << pmtExecTimes[i][target] << endl;


				start = getMilliCount();
				//Executar pmt com um padrão e usando KMP
				//cout << (("bin/pmt -q -k '"+randomPatterns[i][target]+"' "+targets[target]).c_str()) << endl;
				system (("bin/pmt -q -k '"+randomPatterns[i][target]+"' "+targets[target]).c_str());
				pmtKMPExecTimes[i][target] = getMilliSpan(start);//difftime( time(0), start); //(double)(clock() - tStart)/CLOCKS_PER_SEC;
				//cout << pmtKMPExecTimes[i][target] << endl;

				start = getMilliCount();
				//Executar grep com um padrão
				//cout << (("grep -q '"+randomPatterns[i][target]+"' "+targets[target]).c_str()) << endl;
				system (("grep -q '"+randomPatterns[i][target]+"' "+targets[target]).c_str());
				grepExecTimes[i][target] = getMilliSpan(start);//difftime( time(0), start); //(double)(clock() - tStart)/CLOCKS_PER_SEC;
				//cout << grepExecTimes[i][target] << endl;

				for (k = 0; k < editCount; k++)	{
				
					start = getMilliCount();
					//Executar pmt aproximado com um padrão
					//cout << (("bin/pmt -q -e="+editDistances[k]+" '"+randomPatterns[i][target]+"' "+targets[target]).c_str()) << endl;
					system (("bin/pmt -q -e="+editDistances[k]+" '"+randomPatterns[i][target]+"' "+targets[target]).c_str());
					pmtApproxExecTimes[i][target][k] = getMilliSpan(start);//difftime( time(0), start); //(double)(clock() - tStart)/CLOCKS_PER_SEC;
					//cout << pmtApproxExecTimes[i][target][k] << endl;

					//TODO output suppression not working
					//Executar agrep com um padrão
					/*tStart = clock();
					system (("agrep -"+editDistances[k]+" -q '"+randomPatterns[i][j]+"' "+target).c_str());
					agrepExecTimes[i][j][k] = (double)(clock() - tStart)/CLOCKS_PER_SEC;	*/
				
			}
		}
	}

	//Em segundos
	ofstream myfile;
	myfile.open ("results.txt");
	//myfile << "Writing this to a file.\n";
	
	myfile << "Results (n milliseconds)\n";
	for (target = 0; target < targetsCount; target++) {
		myfile << "Target " << targets[target] << ":\n";
		myfile << "\nPMT (Boyer):\n";
		for (i = 0; i < patLens; i++) {
			myfile << pmtExecTimes[i][target] << " ";
		}
		myfile << "\nPMT (KMP):\n";
		for (i = 0; i < patLens; i++) {
			myfile << pmtKMPExecTimes[i][target] << " ";
		}
		myfile << "\nGREP:\n";
		for (i = 0; i < patLens; i++) {
			myfile << grepExecTimes[i][target] << " ";
		}
		myfile << "\nPMT (Sellers):\n";
	
		for (k = 0; k < editCount; k++) {
			myfile << "With edit distance=" << editDistances[k] << "\n";
			for (i = 0; i < patLens; i++) {
				myfile << pmtApproxExecTimes[i][target][k] << " ";
			}
		}
	}


	/*printf("\nCalculating averages (in seconds)...");

	float acc;
	printf("\nPMT (BOYER)\n");
	for (i = 0; i < patLens; i++) {
		acc = 0;
		printf("\nPMT (BOYER)\n");
		for (j = 0; j < targetsCount; j++) {
			acc += pmtExecTimes[i][j];
		}
		printf("%.6f ", acc/patsPerLen);
	}

	printf("\nPMT (KMP)\n");
	for (i = 0; i < patLens; i++) {
		acc = 0;
		for (j = 0; j < patsPerLen; j++) {
			acc += pmtKMPExecTimes[i][j];
		}
		printf("%.6f ", acc/patsPerLen);
	}

	printf("\nGREP\n");
	for (i = 0; i < patLens; i++) {
		acc = 0;
		for (j = 0; j < patsPerLen; j++) {
			acc += grepExecTimes[i][j];
		}
		printf("%.6f ", acc/patsPerLen);
	}*/

	/*printf("\nPMT (APPROX)");
	for (k = 0; k < editCount; k++) {
		printf("\nWith edit distance=%s\n", editDistances[k].c_str());
		for (i = 0; i < patLens; i++) {
			acc = 0;
			for (j = 0; j < patsPerLen; j++) {
				acc += pmtApproxExecTimes[i][j][k];
			}
			printf("%.6f ", acc/patsPerLen);
		}
	}*/

	//TODO output suppression not working
	/*printf("\nAGREP\n");
	for (k = 0; k < editCount; k++) {
		acc = 0;
		printf("With edit distance=%s\n", editDistances[k].c_str());
		for (i = 0; i < patLens; i++) {
			for (j = 0; j < patsPerLen; j++) {
				acc += agrepExecTimes[i][j][k];
			}
		}
		printf("%.6f ", acc/agrepExecTimes[i][j][k]);
	}*/

	myfile.close();
	//printf("\n\n");
	return 0;
}