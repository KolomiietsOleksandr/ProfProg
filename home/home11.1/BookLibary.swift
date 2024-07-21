import Foundation

let books = [
    "The Topographer’s Clown",
    "The Chamber of Beaver",
    "The Ironer of Kanban",
    "The Piglet of Tire",
    "The Border of the Unix",
    "The Half-Time Convince",
    "The Earthly Pillows",
    "The Censorship of the Ping",
    "The True Powers",
    "The Overturn of the Ling"
]

func shuffle<T>(_ array: [T]) -> [T] {
    var array = array
    for i in array.indices.dropLast() {
        let j = Int.random(in: i..<array.endIndex)
        array.swapAt(i, j)
    }
    return array
}

print("Please enter your name:")
guard let name = readLine(), !name.isEmpty else {
    print("Name cannot be empty.")
    exit(1)
}

let shuffledBooks = shuffle(books)

for book in shuffledBooks {
    print("We recommend: \(book)")
    print("Do you like this book? (yes/no): ", terminator: "")

    guard let response = readLine()?.lowercased() else {
        continue
    }

    if response == "yes" {
        print("Enjoy your book!")
        exit(0)
    }
}

print("Au revoir, \(name)!")
exit(0)
