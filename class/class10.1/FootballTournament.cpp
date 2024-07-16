#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iomanip>
#include <ranges>

class Team {
public:
    std::string name;
    int goals_scored = 0;
    int goals_conceded = 0;
    int yellow_cards = 0;
    int red_cards = 0;
    double top_heights = 0.0;
    double points = 0.0;

    Team(std::string team_name) : name(std::move(team_name)) {}

    void update_stats(int goals_scored, int goals_conceded, int yellow_cards, int red_cards, double top_height) {
        this->goals_scored += goals_scored;
        this->goals_conceded += goals_conceded;
        this->yellow_cards += yellow_cards;
        this->red_cards += red_cards;
        this->top_heights += top_height;
    }
};

class Match {
public:
    Team* team1;
    Team* team2;
    int goals_team1, goals_team2;
    int yellow_team1, yellow_team2;
    int red_team1, red_team2;
    double height_team1, height_team2;

    Match(Team* t1, Team* t2, int g1, int g2, int y1, int y2, int r1, int r2, double h1, double h2)
        : team1(t1), team2(t2), goals_team1(g1), goals_team2(g2),
          yellow_team1(y1), yellow_team2(y2), red_team1(r1), red_team2(r2),
          height_team1(h1), height_team2(h2) {}

    void play_match() {
        team1->update_stats(goals_team1, goals_team2, yellow_team1, red_team1, height_team1);
        team2->update_stats(goals_team2, goals_team1, yellow_team2, red_team2, height_team2);

        if (goals_team1 > goals_team2) {
            team1->points += 3.14;
            team2->points -= 0.5;
        } else if (goals_team1 < goals_team2) {
            team2->points += 3.14;
            team1->points -= 0.5;
        } else {
            team1->points += 2.71828;
            team2->points += 2.71828;
        }
    }
};

class Tournament {
public:
    std::vector<Team> teams;
    std::vector<Match> matches;

    void add_team(const std::string& name) {
        teams.emplace_back(name);
    }

    void add_match(const std::string& team1_name, const std::string& team2_name, int goals1, int goals2,
                   int yellow1, int yellow2, int red1, int red2, double height1, double height2) {
        Team* team1 = find_team(team1_name);
        Team* team2 = find_team(team2_name);
        matches.emplace_back(team1, team2, goals1, goals2, yellow1, yellow2, red1, red2, height1, height2);
    }

    void play_tournament() {
        for (auto& match : matches) {
            match.play_match();
        }
    }

    void calculate_rankings() {
        std::sort(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
            if (a.points != b.points) return a.points > b.points;
            if (a.top_heights != b.top_heights) return a.top_heights > b.top_heights;
            int goal_delta_a = a.goals_scored - a.goals_conceded;
            int goal_delta_b = b.goals_scored - b.goals_conceded;
            if (goal_delta_a != goal_delta_b) return goal_delta_a > goal_delta_b;
            if (a.goals_scored != b.goals_scored) return a.goals_scored > b.goals_scored;
            if (a.red_cards != b.red_cards) return a.red_cards < b.red_cards;
            if (a.yellow_cards != b.yellow_cards) return a.yellow_cards < b.yellow_cards;
            return std::rand() % 2 == 0; // Random tie breaker
        });
    }

    void display_results() {
        std::cout << std::left << std::setw(15) << "Team" << std::setw(10) << "Points" << std::setw(15) << "Top Heights"
                  << std::setw(10) << "Goals" << std::setw(10) << "Yellow" << std::setw(10) << "Red" << std::endl;
        for (const auto& team : teams) {
            std::cout << std::left << std::setw(15) << team.name << std::setw(10) << team.points << std::setw(15) << team.top_heights
                      << std::setw(10) << team.goals_scored << std::setw(10) << team.yellow_cards << std::setw(10) << team.red_cards << std::endl;
        }
    }

private:
    Team* find_team(const std::string& name) {
        auto it = std::ranges::find_if(teams, [&name](const Team& team) { return team.name == name; });
        return it != teams.end() ? &(*it) : nullptr;
    }
};

int main() {
    Tournament tournament;
    std::vector<std::string> team_names = {"Team1", "Team2", "Team3", "Team4"};
    for (const auto& name : team_names) {
        tournament.add_team(name);
    }

    tournament.add_match("Team1", "Team2", 1, 2, 1, 0, 0, 1, 10.5, 12.0);
    tournament.add_match("Team1", "Team3", 3, 3, 2, 2, 0, 0, 9.8, 10.0);
    tournament.add_match("Team1", "Team4", 2, 1, 1, 1, 1, 0, 8.0, 7.5);
    tournament.add_match("Team2", "Team3", 1, 1, 0, 1, 0, 1, 11.0, 11.5);
    tournament.add_match("Team2", "Team4", 2, 2, 1, 1, 1, 1, 10.0, 9.5);
    tournament.add_match("Team3", "Team4", 3, 2, 2, 1, 0, 0, 12.0, 13.0);

    tournament.play_tournament();
    tournament.calculate_rankings();
    tournament.display_results();

    return 0;
}
