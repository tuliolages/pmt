#include "tests.h"

using namespace std;

//Temporary simple alphabet
static const char alphanum[] =
	"0123456789"
	"!@#$%^&*"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

// Random string generator function.
char genRandom()
{

    return alphanum[rand() % stringLength];
}

int main() {
	const int patLens = 12;
	const int patsPerLen = 50;
	const int editCount = 4;
	string editDistances[editCount] = {"0", "1", "4", "8"};
	string randomPatterns[patLens][patsPerLen]; //500 de cada tamanho, 12, indo de 2 até 4096
	

	printf("\nGenerating patterns (%d pattern(s) per length, lenght(s) from 2 to 2^%d)...\n", patsPerLen, patLens);

	int i, j, k;
	int patLen = 2;
	for (i = 0; i < patLens; i++)	{
		for (j = 0; j < patsPerLen;j++) {
			for (k = 0; k < patLen; k++) {
				randomPatterns[i][j] += genRandom();
			}
		}
		patLen *= 2;
	}

	string target = "data/*/*";

	float pmtExecTimes[patLens][patsPerLen]; 					// pmt exato com boyer moore com 1 padrão
	float pmtKMPExecTimes[patLens][patsPerLen]; 				// pmt exato com kmp com 1 padrão
	float grepExecTimes[patLens][patsPerLen];					// grep com 1 padrão
	float pmtApproxExecTimes[patLens][patsPerLen][editCount];	// pmt aproximado com sellers com 1 padrão
	float agrepExecTimes[patLens][patsPerLen][editCount];		// agrep com 1 padrão

	clock_t tStart;

	printf("Searching...\n");

	for (i = 0; i < patLens; i++)	{
		printf("Patterns with length 2^%d...\n", (i+1));
		for (j = 0; j < patsPerLen; j++) {

			//Executar pmt com um padrão
			tStart = clock();
			system (("bin/pmt -q '"+randomPatterns[i][j]+"' "+target).c_str());
			pmtExecTimes[i][j] = (double)(clock() - tStart)/CLOCKS_PER_SEC;

			//Executar pmt com um padrão e usando KMP
			tStart = clock();
			system (("bin/pmt -q -k '"+randomPatterns[i][j]+"' "+target).c_str());
			pmtKMPExecTimes[i][j] = (double)(clock() - tStart)/CLOCKS_PER_SEC;

			//Executar grep com um padrão
			tStart = clock();
			system (("grep -q '"+randomPatterns[i][j]+"' "+target).c_str());
			grepExecTimes[i][j] = (double)(clock() - tStart)/CLOCKS_PER_SEC;


			for (k = 0; k < editCount; k++)	{
			
				//Executar pmt aproximado com um padrão
				tStart = clock();
				system (("bin/pmt -q -e="+editDistances[k]+" '"+randomPatterns[i][j]+"' "+target).c_str());
				pmtApproxExecTimes[i][j][k] = (double)(clock() - tStart)/CLOCKS_PER_SEC;

				//TODO output suppression not working
				//Executar agrep com um padrão
				/*tStart = clock();
				system (("agrep -"+editDistances[k]+" -q '"+randomPatterns[i][j]+"' "+target).c_str());
				agrepExecTimes[i][j][k] = (double)(clock() - tStart)/CLOCKS_PER_SEC;	*/
			}
		}
	}

	//Em segundos
	printf("\nCalculating averages (in seconds)...");

	float acc;
	printf("\nPMT (BOYER)\n");
	for (i = 0; i < patLens; i++) {
		acc = 0;
		for (j = 0; j < patsPerLen; j++) {
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
	}

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

	printf("\n\n");
return 0;
}