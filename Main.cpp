#include "CompleteReg.h"

int main() {
	CompleteReg cr;

	cr.displayAllTeams();
	cr.displayTeam("Alibaba");
	cr.displayPlayer("Ali");

	cr.addTeam("Galatasaray", "Red", 1905);
	cr.addTeam("GAlatasaray", "Yellow", 1905);
	cr.addTeam("Fenerbahce", "Yellow", 1907);
	cr.addTeam("Besiktas", "White", 1908);
	cr.addTeam("Trabzonspor", "Blue", 1967);
	cr.addTeam("Antalyaspor", "White", 2021);

	cr.displayAllTeams();
	cr.displayTeam("Trabzonspor");

	cr.addPlayer("Trabzonspor", "Yattara", "center");
	cr.addPlayer("Trabzonspor", "Hami Mandirali", "forward");
	cr.addPlayer("Galatasaray", "Burak Yilmaz", "forward");
	cr.addPlayer("Besiktas", "Burak Yilmaz", "forward");
	cr.addPlayer("Antalyaspor", "Eto", "forward");
	cr.addPlayer("Fenerbahce", "Kaleci Volkan", "goalkeeper");

	cr.displayAllTeams();
	cr.displayTeam("Trabzonspor");
	cr.displayTeam("Besiktas");
	cr.displayPlayer("Burak Yilmaz");
	cr.displayPlayer("Yattara");

	cr.removePlayer("Trabzonspor", "Yattara");
	cr.displayTeam("Trabzonspor");

	cr.displayAllTeams();

	cr.removeTeam("Besiktas");

	cr.displayAllTeams();

	return 1;
}