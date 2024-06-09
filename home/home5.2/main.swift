import Foundation

class Configuration {
    static let shared = Configuration()
    private var config: [ClosedRange<Character>: (pre: String, post: String)] = [:]
    
    private init() {
        loadConfig()
    }
    
    private func loadConfig() {
        let configFilePath = "config.txt"
        guard let content = try? String(contentsOfFile: configFilePath) else {
            print("Failed to load configuration file.")
            return
        }
        
        let lines = content.split(separator: "\n")
        for line in lines {
            let parts = line.split(separator: " ")
            guard parts.count == 3 else { continue }
            let rangeString = String(parts[0])
            let preWord = String(parts[1])
            let postWord = String(parts[2])
            
            let rangeParts = rangeString.split(separator: "-")
            if rangeParts.count == 2,
               let start = rangeParts.first?.first,
               let end = rangeParts.last?.first {
                let range = start...end
                config[range] = (pre: preWord, post: postWord)
            }
        }
    }
    
    func getPreAndPostWord(for word: String) -> (String, String)? {
        guard let firstChar = word.lowercased().first else { return nil }
        for (range, words) in config {
            if range.contains(firstChar) {
                return words
            }
        }
        return nil
    }
}

func main() {
    print("Enter your 5 favorite words:")
    var favoriteWords: [String] = []
    
    for _ in 0..<5 {
        if let word = readLine() {
            favoriteWords.append(word)
        }
    }
    
    let group = DispatchGroup()
    
    for word in favoriteWords {
        group.enter()
        DispatchQueue.global().async {
            Thread.sleep(forTimeInterval: 1)
            if let (preWord, postWord) = Configuration.shared.getPreAndPostWord(for: word) {
                print("\(preWord) \(word) \(postWord)")
            } else {
                print("Configuration not found for word: \(word)")
            }
            group.leave()
        }
    }
    
    group.wait()
}

main()
