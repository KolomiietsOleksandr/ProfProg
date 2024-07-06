import Foundation

enum Song: String {
    case intro = "Intro"
    case starman = "Starman"
    case showMustGoOn = "Show must go on"
    case letItBe = "Let it be"
    case inTheEnd = "But in the end, it doesn't even matter"
}

enum Command: String {
    case sad = "sad"
    case fun = "fun"
    case silly = "silly"
    case dangerous = "dangerous"
}

class StateMachine {
    var currentState: Song = .intro

    func transition(command: Command) {
        switch currentState {
        case .intro:
            switch command {
            case .dangerous:
                currentState = .letItBe
            case .fun:
                currentState = .starman
            case .sad:
                currentState = .inTheEnd
            default:
                break
            }
        case .starman:
            switch command {
            case .silly:
                currentState = .intro
            case .dangerous:
                currentState = .showMustGoOn
            case .fun:
                currentState = .inTheEnd
            default:
                break
            }
        case .showMustGoOn:
            switch command {
            case .sad:
                currentState = .letItBe
            case .fun:
                currentState = .starman
            default:
                break
            }
        case .letItBe:
            switch command {
            case .dangerous:
                currentState = .intro
            case .silly:
                currentState = .showMustGoOn
            default:
                break
            }
        case .inTheEnd:
            print("Program terminated.")
            exit(0)
        }
        print("Playing: \(currentState.rawValue)")
    }
}

let stateMachine = StateMachine()
print("Playing: \(stateMachine.currentState.rawValue)")

while true {
    print("Enter a command (sad, fun, silly, dangerous): ", terminator: "")
    if let input = readLine(), let command = Command(rawValue: input) {
        stateMachine.transition(command: command)
    } else {
        print("Invalid command. Please try again.")
    }
}
