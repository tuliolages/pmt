#include <string.h>
#include <stdio.h>
#include <iostream>

#define NUMBER_OF_CHARS 256

using namespace std;

int max (int a, int b) { return (a > b)? a: b; }

int brd(char *pat, int j) {
	int m = strlen(pat);
	int l = j-1;
	int k;
	while (l>=0) {
		k = 0;
		while (k<1 && pat[k]==pat[j-l+k])
			k += 1;
		if (k==l)
			return l;
		l--;
	}

	return -1;
}

int* borders(char *pat, int *B) {
	int m = strlen(pat);
	//int B [m+1]; //TODO new e delete
	int i;
	B[0] = -1;
	for (i = 0; i < m; i++)
		B[i] = 0;
	i = 1;
	int j = 0;
	while (i<m) {
		while(i+j<m && pat[j]==pat[i+j]) {
			j += 1;
			B[i+j]=j;
		}
		i += (j-B[j]);
		j = max(0, B[j]);
	}
	return B;
}

void good_suffix_heuristic(char *pat, int m, int gs [m+1]) {
	int Pi [m+1];
	borders(pat, Pi);
	int PiR [m+1];
	int i;
	//TODO juntar os fors
	for (i = 0; i < m+1; i++) {
		PiR[i] = Pi[m-i];
	}
	gs[0] = m+1
	for (i = 1; i < m+1; i++) {
		gs[i] = m-Pi[m];
	}

	int j;
	for (i = 1; i < m; i++) {
		j = m-1-PiR[i];
		if (gs[j] > i-PiR[i])
			gs[j] = i-PiR[i];
	}
}

void bad_character_heuristic(char *pat, int m, int bc[NUMBER_OF_CHARS]) {
	int i;
	
	for (i = 0; i < NUMBER_OF_CHARS; i++) {
		bc[i] = -1;
	}
	
	for (i = 0; i < m; i++) {
		bc[(int) pat[i]] = i;
	}
}

void search(char *txt, char *pat) {
	int n = strlen(txt);
	int m = strlen(pat);

	int bc[NUMBER_OF_CHARS];
	bad_character_heuristic(pat, m, bc);
	int gs[m+1]; //TODO
	good_suffix_heuristic(pat, m, gs);

	int i = 0;

	while (i < n-m+1) {
		int j = m-1;
		cout << j << endl;
		while(j>=0 && txt[i+j]==pat[j]) {
			cout << txt[i+1] << "-" << pat[j] << endl;
			j -= 1;
		}
		if (j<0) {
			cout << "treta found @" << i << endl;
			i += (i+m < n) ? m-bc[txt[i+m]] : 1;
		} else {
			i += max(1, (j-bc[txt[i+j]]));
			cout << "pular " << i << endl; 
		}
	}
}

int main() {

	search("Robertsonovelinojuniornovelintrobertsinrobertsonsonson", "oberts");

	return 0;
}

/*


import sys

def brute_force(txt, pat):
    occ = []
    n = len(txt)
    m = len(pat)
    i = 0
    j = 0
    while i < n-m+1:
        #print
        #print "   %si=%d"%(i*" ",i)
        #print "T: %s"%txt
        j = 0
        while j<m and txt[i+j]==pat[j]:
            j += 1
        #print "   %s%s%s"%(i*" ", (j)*"=", "" if j==m else "!")
        #print "P: %s%s"%(i*" ", pat)
        #print "   %sj=%d"%(i*" ", j)
        if j==m:
            occ.append(i)
        j = 0
        i += 1
    return occ


def sbrd(pat, j):
    m = len(pat)
    l = j-1
    while l>=0:
        k = 0
        while k<l and pat[k]==pat[j-l+k]:
            k +=1
        if k==l and (j==m or pat[k]!=pat[j]):
            return l
        l -= 1
    return -1


def init_next(pat):
    m = len(pat)
    B = (m+1)*[-1]
    if m==1 or ( m>1 and pat[0]!=pat[1]):
        B[1]=0
    i = 1
    j = 0
    while i<m:
        while (i+j)<m and pat[j]==pat[i+j]:
            j += 1
            if (i+j)==m or pat[i+j]!=pat[j]:
                B[i+j]=j
            else:
                B[i+j]=B[j]
        if j==0 and pat[0]!=pat[i]:
            B[i+1]=0
        i += (j-B[j])
        j = max(0,B[j]) 
    return B



def kmp(txt, pat):
    nxt = init_next(pat)
    occ = []
    n = len(txt)
    m = len(pat)
    i = 0
    j = 0
    while i < n-m+1:
        #print
        #print "   %si=%d"%(i*" ",i)
        #print "T: %s"%txt
        while j<m and txt[i+j]==pat[j]:
            j += 1
        #print "   %s%s%s"%(i*" ", (j)*"=", "" if j==m else "!")
        #print "P: %s%s"%(i*" ", pat)
        #print "   %sj=%d"%(i*" ", j)
        if j==m:
            occ.append(i)
        sb = sbrd(pat,j)
        if (sb!=nxt[j]):
		    print "sb(%d)=%d nxt[%d]=%d"%(j,sb,j,nxt[j])
            #exit(1)
        assert(sb==nxt[j])
        #print "   %ssb=%d"%(i*" ", sb)
        i += j - sb
        j = max(0, sb)
    return occ


def brd(pat, j):
    m = len(pat)
    l = j-1
    while l>=0:
        k = 0
        while k<l and pat[k]==pat[j-l+k]:
            k +=1
        if k==l:
            return l
        l -= 1
    return -1


def borders(pat):
    m = len(pat)
    B = [-1]+m*[0]
    i = 1
    j = 0
    while i<m:
        while (i+j)<m and pat[j]==pat[i+j]:
            j += 1
            B[i+j]=j
        #if j==0 and pat[0]!=pat[i]:
        #    B[i+1]=0
        i += (j-B[j])
        j = max(0,B[j]) 
    assert(B==[brd(pat,k) for k in range(0,m+1)])
    return B

def good_suffix(pat):
    m = len(pat)
    Pi = borders(pat)
    PiR = borders(pat[::-1])
    S = (m+1)*[m-Pi[m]]
    for l in range(1,m):
        j =  m-1-PiR[l]
        assert(j>=0 and j<m)
        if S[j] > l-PiR[l]:
            S[j] =  l-PiR[l]
    print S
    return S

def bad_char(pat):
    ret = {}
    p = 0
    for a in pat:
        ret[a] = p
        p += 1
    return ret


def bm(txt, pat):
    bc = bad_char(pat)
    gs = good_suffix(pat)
    occ = []
    n = len(txt)
    m = len(pat)
    i = 0
    while i < n-m+1:
        j = m-1
        print
        print "   %si=%d"%(i*" ",i)
        print "T: %s"%txt
        while j>=0 and txt[i+j]==pat[j]:
            j -= 1
        print "   %s%s%s"%((i+max(0,j))*" ", '!' if j>=0 else '', (m-1-j)*"=")
        print "P: %s%s"%(i*" ", pat)
        print "   %sj=%d"%(i*" ", j)
        if j<0:
            occ.append(i)
        bcskip = (j-bc[txt[i+j]]) if (j>0 and txt[i+j] in bc) else j+1
        gsskip = gs[j] 
        i += max([bcskip, gsskip])
    return occ



def main():
    print good_suffix("ABABBABBAAAAABBABB")
    
    ftxt = open(sys.argv[1], "r")
    txt = ""
    for line in [x.strip() for x in ftxt]:
		txt = txt + line
    #print "TXT=\"%s\""%txt
    ftxt.close()
    fpat = open(sys.argv[2], "r")
    for pat in fpat:
        pat = pat.strip()
        print "PAT=\"%s\""%pat
        occ = brute_force(txt, pat)
        print "BFC OCC=", occ
        occ = bm(txt, pat)
        print "BM  OCC=", occ
    fpat.close()
    #print "kmp rocks!"



if __name__ == '__main__':
    main()
*/