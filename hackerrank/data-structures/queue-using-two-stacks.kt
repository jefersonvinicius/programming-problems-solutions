import java.io.*
import java.util.*

class Queue {
    lateinit var elements: MutableList<Int>

    constructor() {
        elements = mutableListOf<Int>()
    }

    fun front(): Int {
        return elements[0]
    }

    fun enqueue(element: Int) {
        elements.add(element)
    }

    fun dequeue(): Int {
        val element = elements[0]
        elements.removeAt(0)
        return element
    }
}

fun proccessQueries(operations: Array<String>) {
    val queue = Queue()

    for (operation in operations) {
        if (operation[0] == '1') {
            val element = operation.substring(2).toInt()
            queue.enqueue(element)
        }
        if (operation[0] == '2') {
            queue.dequeue()
        }
        if (operation[0] == '3') {
            println(queue.front())
        }
    }

}

fun main(args: Array<String>) {
    val scan = Scanner(System.`in`)
    val q = scan.nextLine().trim().toInt()

    val operations = Array<String>(q){""}
    for (i in 0..q - 1) {
        val operation = scan.nextLine()
        operations[i] = operation
    }

    proccessQueries(operations)

}