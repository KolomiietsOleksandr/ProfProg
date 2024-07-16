import Foundation

class Team {
    var name: String
    var goalsScored: Int = 0
    var goalsConceded: Int = 0
    var yellowCards: Int = 0
    var redCards: Int = 0
    var topHeights: Double = 0.0
    var points: Double = 0.0

    init(name: String) {
        self.name = name
    }

    func updateStats(goalsScored: Int, goalsConceded: Int, yellowCards: Int, redCards: Int, topHeight: Double) {
        self.goalsScored += goalsScored
        self.goalsConceded += goalsConceded
        self.yellowCards += yellowCards
        self.redCards += redCards
        self.topHeights += topHeight
    }
}

class Match {
    var team1: Team
    var team2: Team
    var goalsTeam1: Int
    var goalsTeam2: Int
    var yellowTeam1: Int
    var yellowTeam2: Int
    var redTeam1: Int
    var redTeam2: Int
    var heightTeam1: Double
    var heightTeam2: Double

    init(team1: Team, team2: Team, goalsTeam1: Int, goalsTeam2: Int, yellowTeam1: Int, yellowTeam2: Int,
         redTeam1: Int, redTeam2: Int, heightTeam1: Double, heightTeam2: Double) {
        self.team1 = team1
        self.team2 = team2
        self.goalsTeam1 = goalsTeam1
        self.goalsTeam2 = goalsTeam2
        self.yellowTeam1 = yellowTeam1
        self.yellowTeam2 = yellowTeam2
        self.redTeam1 = redTeam1
        self.redTeam2 = redTeam2
        self.heightTeam1 = heightTeam1
        self.heightTeam2 = heightTeam2
    }

    func playMatch() {
        team1.updateStats(goalsScored: goalsTeam1, goalsConceded: goalsTeam2, yellowCards: yellowTeam1, redCards: redTeam1, topHeight: heightTeam1)
        team2.updateStats(goalsScored: goalsTeam2, goalsConceded: goalsTeam1, yellowCards: yellowTeam2, redCards: redTeam2, topHeight: heightTeam2)

        if goalsTeam1 > goalsTeam2 {
            team1.points += 3.14
            team2.points -= 0.5
        } else if goalsTeam1 < goalsTeam2 {
            team2.points += 3.14
            team1.points -= 0.5
        } else {
            team1.points += 2.71828
            team2.points += 2.71828
        }
    }
}

class Tournament {
    var teams: [Team] = []
    var matches: [Match] = []

    func addTeam(name: String) {
        teams.append(Team(name: name))
    }

    func addMatch(team1Name: String, team2Name: String, goals1: Int, goals2: Int,
                  yellow1: Int, yellow2: Int, red1: Int, red2: Int, height1: Double, height2: Double) {
        if let team1 = findTeam(name: team1Name), let team2 = findTeam(name: team2Name) {
            matches.append(Match(team1: team1, team2: team2, goalsTeam1: goals1, goalsTeam2: goals2, yellowTeam1: yellow1,
                                 yellowTeam2: yellow2, redTeam1: red1, redTeam2: red2, heightTeam1: height1, heightTeam2: height2))
        } else {
            print("Error: One of the teams not found")
        }
    }

    func playTournament() {
        for match in matches {
            match.playMatch()
        }
    }

    func calculateRankings() {
        teams.sort {
            if $0.name.lowercased() == "russia" { return false }
            if $1.name.lowercased() == "russia" { return true }
            if $0.points != $1.points { return $0.points > $1.points }
            if $0.topHeights != $1.topHeights { return $0.topHeights > $1.topHeights }
            let goalDeltaA = $0.goalsScored - $0.goalsConceded
            let goalDeltaB = $1.goalsScored - $1.goalsConceded
            if goalDeltaA != goalDeltaB { return goalDeltaA > goalDeltaB }
            if $0.goalsScored != $1.goalsScored { return $0.goalsScored > $1.goalsScored }
            if $0.redCards != $1.redCards { return $0.redCards < $1.redCards }
            if $0.yellowCards != $1.yellowCards { return $0.yellowCards < $1.yellowCards }
            return Bool.random()
        }

        if let russiaIndex = teams.firstIndex(where: { $0.name.lowercased() == "russia" }) {
            let russiaTeam = teams.remove(at: russiaIndex)
            teams.append(russiaTeam)
        }
    }

    func displayResults() {
        print("Team\t\tPoints\tTop Heights\tGoals\tYellow\tRed")
        for team in teams {
            print("\(team.name)\t\(team.points)\t\(team.topHeights)\t\(team.goalsScored)\t\(team.yellowCards)\t\(team.redCards)")
        }
    }

    private func findTeam(name: String) -> Team? {
        return teams.first { $0.name == name }
    }
}

let tournament = Tournament()
let teamNames = ["Team1", "Team2", "Team3", "russia"]
for name in teamNames {
    tournament.addTeam(name: name)
}

tournament.addMatch(team1Name: "Team1", team2Name: "Team2", goals1: 1, goals2: 2, yellow1: 1, yellow2: 0, red1: 0, red2: 1, height1: 10.5, height2: 12.0)
tournament.addMatch(team1Name: "Team1", team2Name: "Team3", goals1: 3, goals2: 3, yellow1: 2, yellow2: 2, red1: 0, red2: 0, height1: 9.8, height2: 10.0)
tournament.addMatch(team1Name: "Team1", team2Name: "russia", goals1: 2, goals2: 1, yellow1: 1, yellow2: 1, red1: 1, red2: 0, height1: 8.0, height2: 7.5)
tournament.addMatch(team1Name: "Team2", team2Name: "Team3", goals1: 1, goals2: 1, yellow1: 0, yellow2: 1, red1: 0, red2: 1, height1: 11.0, height2: 11.5)
tournament.addMatch(team1Name: "Team2", team2Name: "russia", goals1: 2, goals2: 2, yellow1: 1, yellow2: 1, red1: 1, red2: 1, height1: 10.0, height2: 9.5)
tournament.addMatch(team1Name: "Team3", team2Name: "russia", goals1: 3, goals2: 2, yellow1: 2, yellow2: 1, red1: 0, red2: 0, height1: 12.0, height2: 13.0)

tournament.playTournament()
tournament.calculateRankings()
tournament.displayResults()
