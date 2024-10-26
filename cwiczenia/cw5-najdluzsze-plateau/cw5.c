#include <stdio.h>


/**
	Wzorcowe rozwiązanie. Niezmiennik jest tutaj trochę bardziej skomplikowany niż w plateau_unsorted_1() i zawiera dwa twierdzenia w jednym:

	N(i,max,lok): 
	* lok jest długością maksymalnego plateau w podtablicy a[0..i-1] kończącego się w a[i-1].
	* max jest długością maksymalnego plateau w podtablicy a[0..i-lok]. (**Na ćwiczeniach zacznij od a[0..i-1] i zobacz że automatycznie dojdziemy do a[0..i-lok].**) [lub do a[0..i-1-lok], wtedy startuj z max=0]
*/
int plateau_unsorted(int a[], int n) 
{
	int i=1, max=1, lok=1; // N(1) spełnione (podtablica zawiera tylko a[0])
	while (i < n) 
	{  // Zakładamy że N(i) spełnione; chcemy pokazać że pod koniec iteracji też N(i+1) spełnione
		if (a[i] == a[i-1]) 
		{
			++lok; // N(i+1): Warunek 1 oczywisty, warunek 2 ponieważ wartość (i+1)-lok ta sama jak przedtem dla i z starym lok.
		}
		else 
		{  // a[i]!=a[i-1] 
			if (lok > max) 
			{
				max = lok; 
				/* max = jest teraz długością najdłuższego plateau w a[0..(i+1)-1]
				(Ponieważ maksymalne plateau są rozłączne, to najdłuższe plateau
				jest albo a[i-lok..(i+1)-1] (zatem długość lok) lub znajduje się 
				w a[0..(i+1)-lok-1] \subset a[0..(i+1)-lok] (zatem długość max).  */
			}
			lok = 1; 
			// lok=1; więc w sumie N(i+1) spełnione. 
		}
		++i; //Więc N(i) zachodzi też na początku następnej iteracji
	}
	/* Teraz i=n; 
	max jest zagwarantowane byciem globalnym maksem tylko jeśli lok==1 w N(n). 
	Jeśli lok>1, to nie mamy tej gwarancji i wiemy tylko że albo plateau się kończy na a[n-1] (i poprawne rozwiązanie jest lok) lub się nie kończy na a[n-1] (a więc jest zawarte w podtablicy a[0..n-lok-1] i poprawne rozwiązanie jest max). Więc brakuje jeszcze jedno obliczenie:*/
	if (lok > max) 
	{
		return lok;
	}
	else
	{
		return max; //Można ominąć "else", bo z return powyżej tak i tak wyskoczymy z funkcji. Ale tak jak teraz to logika programu jest bardziej przejrzysta.
	}
}

/**  
	Rozwiązanie zaproponowane kiedyś na ćwiczeniach. Ma całkiem przejrzyste dwa niezmienniki, ale nie wiem czy na prawdę lepsze

	Niezmiennik dla 1 pętli while:
		N(i): max jest długością maksymalnego plateau w podtablicy a[0..i] oraz (a[i]!=a[i-1] lub i==0 lub i==n-1).
	Niezmiennik dla 2 pętli while:
		N2(i): lok jest długością maksymalnego plateau w podtablicy a[0..i] kończącego się na a[i].
*/
int plateau_unsorted_alt(int a[], int n) 
{
	int i = 0, max = 1; // N(i) spełnione dla i = 0 
	while (i < n -1) 
	{
		// Na początku iteracji: N(i) spełnione
		int lok = 1;
		// Tutaj N2(i) jest też spełnione ponieważ N(i) gwarantuje nam że a[i]!=a[i-1] lub i==0 (przypadek i==n-1 wyłapany przez nagłówek pętli) więc lok=1 jest prawidłowe.
		while (i < n-1 && a[i] == a[i+1]) 
		{
			// Na początku iteracji: N2(i) spełnione.
			// Ponieważ weszliśmy do pętli, to mamy a[i]==a[i+1], więc N2(i+1) też spełnione.
			++lok;
			++i;
		}
		if (lok > max) 
		{
			max = lok; 
			// Więc N(i) spełnione też dla aktualnego 'i'. 
		}
		// Ponieważ wyszliśmy z pętli while, to i==n-1 lub a[i]!=a[i+1].
		// Jeśli i==n-1, to max jest teraz maksem w a[0..n-1] 
		//	 ponieważ N(i) spełnione dla aktualnego i.
		// Jeśli a[i]!=a[i+1], to max jest maksem w a[0..i+1] 
		//	 ponieważ plateau kończące się w a[i+1] ma długość 1 <= max.
		if (i < n-1)
		{
			++i;
		}
		// N(i) spełnione dla aktualnego 'i'
	}
	return max; // Tutaj i=n-1. Ponieważ N(n-1) jest poprawne jak powyżej udowodniono, to N(n-1) gwarantuje nam że return max jest prawidłowe.
}

/** 
	Zakładamy teraz że tablica jest posortowana. Jeśli ktoś by nam powiedział czym jest max, to moglibyśmy max zweryfikować znajdując takie k dla którego a[k]=a[k+max-1] oraz pokazując że dla wszystkich k a[k]!=a[k+max]. Daje to nam następujący niezmiennik: 

		N(i,max): 
			Nieformalnie: 
				max = opt w a[0..i-1] 
			Formalnie:
				1) Istnieje k w [0,i-1] takie że k+max-1<=i-1 (a więc k w [0,i-max]) oraz a[k]=a[k+max-1];
				2) Dla wszystkich k w [0,i-1] takich że k+max<=i-1 (a więc k w [0,i-1-max]) mamy a[k]!=a[k+max]; 
		Z niezmiennika możemy bezpośrednio zbudować algorytm:
*/
int plateau_sorted(int a[], int n) 
{
	int i = 1, max = 1; // N(1) zachodzi (drugi warunek też spełniony ponieważ przedział [0,i-1-max] jest pusty)
	for (; i < n; ++i) // Zakładamy że N(i) zachodzi 
	{ // Pokazujemy że N(i+1) na końcu pętli też zachodzi.
		
		if (a[i] == a[i-max]) 
		{ // Jeśli a[i]==a[i-max], to drugi warunek N(i+1) jest skaleczony dla k=i-max.
			++max; //Naprawiamy to zwiększając max.
		}
		
		/* Jeśli a[i]!=a[i-max], to N(i+1) zachodzi:
			warunek 1): bo zachodził dla N(i) ('max' się nie zmienił)   
			warunek 2): bo zachodził dla N(i), to jeśli skaleczony, to 
						tylko dla k poza [0,i-1-max], więc dla k=i-max; 
						ale założyliśmy że a[i]!=a[i-max]. 
		*/
	}
	return max;
}

/**
	Rozwiązanie jak powyżej, tylko że teraz skaczemy o max jeśli a[i]!=a[i-max].

	Dodajemy trzeci warunek oraz min(i,n):
	
	N(i,max):
		1) Istnieje k w [0,min(i,n)-max] takie że a[k]=a[k+max-1];
		2) Dla wszystkich k w [0,min(i,n)-1-max] mamy a[k]!=a[k+max]; 
		3) Jeśli i < n: a[i]!=a[i-1] lub a[i-1]==a[i-max] 
*/
int plateau_sorted_faster(int a[], int n) 
{
	int i = 1, max = 1;
	while (i < n) // N(i) spełnione
	{
		if (a[i] == a[i-max]) {
			++max;
			++i;
			// Trzeci warunek N(i) też spełniony. Bo warunek if mówił nam że a[(i-1)] == a[(i-1)-(max-1)]
		} 
		else 
		{
			/* Niech j jest aktualną wartością i. 
			
			Trzeci warunek mówi nam że albo a[i]!=a[i-1] lub a[i-1]==a[i-max] co z a[i]!=a[i-max] też implikuje a[i]!=a[i-1]. 
			Więc jeśli istnieje większy max, to musi startować dla jakiegoś i>=j. Sprawdzamy j.
			
			Skaczemy z i do j+max ponieważ jeśli nowy max (większy niż dotychczasowy) startuje dokładnie przy j to musi iść aż do j+max. Potem zmniejszamy i do momentu aż a[i]!= a[i-1].
			
			Jeśli po zmniejszeniu mamy i=j, to a[j]=...=a[j+max], więc istnieje nowy max dla i=j+max (znaleziony w następnej iteracji), w innym przypadku szukamy w następnej iteracji dalej od aktualnej wartości i.*/
			int j = i;
			i += max;
			if (i < n) 
			{
				while (a[i] == a[i-1]) 
				{
					--i;
				}
				if (j == i) 
				{
					i += max;
				}
				// Trzeci warunek N(i) spełniony: 
				// Jeśli weszliśmy do if'a, to mamy teraz a[i]==a[i-1]=...=a[i-max], więc też a[i-1]==a[i-max]
				// Jeśli nie weszliśmy do if'a, to 'i' taki sam jak przy opuszczeniu pętli,
				// a pętle opuściliśmy bo a[i]!=a[i-1].
			}
			/*else
			{	// Więc: i >= n
		
				// N(i) spełnione automatycznie:
				//		Jeśli i >= n, to warunek 1 z N(i) spełniony ponieważ w N(j) spełniony,
				//		a warunek 2, ponieważ z N(j) wiemy a[j]!=a[j-1], a zarazem a[j..n-1] zawiera mniej niż max+1 elementów bo j+max==i >= n.
				//		warunek 3 bo i >= n.
			}*/
		}
	}
	// Na końcu i > n możliwe, z tego powodu używamy min(i,n) w niezmienniku.
	return max;
}

int main(void) {
	int a[] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5};
	int n = sizeof(a) / sizeof(int);
	int len = plateau_sorted_faster(a,n);
	printf("Length of longest plateau: %d", len);
}