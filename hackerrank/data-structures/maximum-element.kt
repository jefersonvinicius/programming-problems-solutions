import java.io.*
import java.math.*
import java.security.*
import java.text.*
import java.util.*
import java.util.concurrent.*
import java.util.function.*
import java.util.regex.*
import java.util.stream.*
import kotlin.collections.*
import kotlin.comparisons.*
import kotlin.io.*
import kotlin.jvm.*
import kotlin.jvm.functions.*
import kotlin.jvm.internal.*
import kotlin.ranges.*
import kotlin.sequences.*
import kotlin.text.*

fun getMax(operations: Array<String>): Array<Int> {
    val stack = mutableListOf<Int>()
    val biggers = mutableListOf<Int>()

    var currentBiggerElement = 0
    var previousBiggerElements = mutableListOf<Int>()

    for (operation in operations) {
        val pieces = operation.split(" ").toTypedArray()

        if (pieces.size > 1) {
            val element = pieces[1].toInt();
            stack.add(element)
            if (element >= currentBiggerElement) {
                currentBiggerElement = element
                previousBiggerElements.add(currentBiggerElement)
            }
        }

        if(pieces[0] == "2" && stack.size > 0) {
            val topElement = stack[stack.size - 1]
            stack.removeAt(stack.size - 1)

            if (topElement == currentBiggerElement) {
                val elementIndexToRemove = previousBiggerElements.indexOfLast{el -> el == topElement}
                previousBiggerElements.removeAt(elementIndexToRemove)
                if (previousBiggerElements.size > 0) {
                    currentBiggerElement = previousBiggerElements[previousBiggerElements.size - 1]
                } else {
                    currentBiggerElement = 0
                }
            }
        }

        if (pieces[0] == "3") {
            biggers.add(currentBiggerElement)
        }
    }

    return biggers.toTypedArray()
}

fun main(args: Array<String>) {
    val n = readLine()!!.trim().toInt()

    val ops = Array<String>(n, { "" })
    for (i in 0 until n) {
        val opsItem = readLine()!!
        ops[i] = opsItem
    }

    val res = getMax(ops)

    println(res.joinToString("\n"))
}
