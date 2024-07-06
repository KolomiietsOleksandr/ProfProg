import Foundation

struct GreenMessage {
    let text: String
    let counter: Int
}

struct BlueMessage {
    let value1: Double
    let value2: Double
}

struct OrangeMessage {
    let text1: String
    let text2: String
    let integer: Int
    let value: Double
}

class MessageDispatcher {
    private var greenSubscribers: [UUID: (GreenMessage) -> Void] = [:]
    private var blueSubscribers: [UUID: (BlueMessage) -> Void] = [:]
    private var orangeSubscribers: [UUID: (OrangeMessage) -> Void] = [:]
    
    private let queue = DispatchQueue(label: "com.message.dispatcher.queue", attributes: .concurrent)
    
    func publishGreenMessage(_ msg: GreenMessage) {
        queue.async(flags: .barrier) {
            self.greenSubscribers.forEach { $0.value(msg) }
        }
    }
    
    func publishBlueMessage(_ msg: BlueMessage) {
        queue.async(flags: .barrier) {
            self.blueSubscribers.forEach { $0.value(msg) }
        }
    }
    
    func publishOrangeMessage(_ msg: OrangeMessage) {
        queue.async(flags: .barrier) {
            self.orangeSubscribers.forEach { $0.value(msg) }
        }
    }
    
    @discardableResult
    func subscribeToGreenMessage(_ callback: @escaping (GreenMessage) -> Void) -> UUID {
        let id = UUID()
        queue.async(flags: .barrier) {
            self.greenSubscribers[id] = callback
        }
        return id
    }
    
    @discardableResult
    func subscribeToBlueMessage(_ callback: @escaping (BlueMessage) -> Void) -> UUID {
        let id = UUID()
        queue.async(flags: .barrier) {
            self.blueSubscribers[id] = callback
        }
        return id
    }
    
    @discardableResult
    func subscribeToOrangeMessage(_ callback: @escaping (OrangeMessage) -> Void) -> UUID {
        let id = UUID()
        queue.async(flags: .barrier) {
            self.orangeSubscribers[id] = callback
        }
        return id
    }
    
    func unsubscribeFromGreenMessage(_ id: UUID) {
        queue.async(flags: .barrier) {
            self.greenSubscribers.removeValue(forKey: id)
        }
    }
    
    func unsubscribeFromBlueMessage(_ id: UUID) {
        queue.async(flags: .barrier) {
            self.blueSubscribers.removeValue(forKey: id)
        }
    }
    
    func unsubscribeFromOrangeMessage(_ id: UUID) {
        queue.async(flags: .barrier) {
            self.orangeSubscribers.removeValue(forKey: id)
        }
    }
}

func generateGreenMessages(dispatcher: MessageDispatcher, group: DispatchGroup) {
    group.enter()
    defer { group.leave() }
    for i in 0..<10 {
        let msg = GreenMessage(text: "GreenMessage_\(i)", counter: Int.random(in: 1...100))
        dispatcher.publishGreenMessage(msg)
        Thread.sleep(forTimeInterval: 0.1)
    }
}

func generateBlueMessages(dispatcher: MessageDispatcher, group: DispatchGroup) {
    group.enter()
    defer { group.leave() }
    for i in 0..<10 {
        let msg = BlueMessage(value1: Double.random(in: 0.0...100.0), value2: Double.random(in: 0.0...100.0))
        dispatcher.publishBlueMessage(msg)
        Thread.sleep(forTimeInterval: 0.15)
    }
}

func generateOrangeMessages(dispatcher: MessageDispatcher, group: DispatchGroup) {
    group.enter()
    defer { group.leave() }
    for i in 0..<10 {
        let msg = OrangeMessage(
            text1: "OrangeMessage1_\(i)",
            text2: "OrangeMessage2_\(i)",
            integer: Int.random(in: 1...100),
            value: Double.random(in: 0.0...100.0)
        )
        dispatcher.publishOrangeMessage(msg)
        Thread.sleep(forTimeInterval: 0.2)
    }
}

let dispatcher = MessageDispatcher()

let greenSubscriptionId = dispatcher.subscribeToGreenMessage { msg in
    print("Received GreenMessage: \(msg.text), \(msg.counter)")
}
let blueSubscriptionId = dispatcher.subscribeToBlueMessage { msg in
    print("Received BlueMessage: \(msg.value1), \(msg.value2)")
}
let orangeSubscriptionId = dispatcher.subscribeToOrangeMessage { msg in
    print("Received OrangeMessage: \(msg.text1), \(msg.text2), \(msg.integer), \(msg.value)")
}

DispatchQueue.global().asyncAfter(deadline: .now() + 1) {
    dispatcher.unsubscribeFromGreenMessage(greenSubscriptionId)
}

let group = DispatchGroup()

DispatchQueue.global().async(group: group) {
    generateGreenMessages(dispatcher: dispatcher, group: group)
}
DispatchQueue.global().async(group: group) {
    generateBlueMessages(dispatcher: dispatcher, group: group)
}
DispatchQueue.global().async(group: group) {
    generateOrangeMessages(dispatcher: dispatcher, group: group)
}

group.wait()
print("All messages generated.")
