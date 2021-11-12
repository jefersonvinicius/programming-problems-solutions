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

fun breakingRecords(scores: Array<Int>): Array<Int> {
    var breakingBest = 0;
    var breakingWorst = 0
    var highest = scores[0];
    var lowest = scores[0]

    for ((index, value) in scores.withIndex()) {
        if (index == 0) continue;

        if (value > highest) {
            breakingBest++
            highest = value
        }
        if (value < lowest) {
            breakingWorst++
            lowest = value
        }
    }

    return arrayOf(breakingBest, breakingWorst)
}

fun main(args: Array<String>) {
    val n = readLine()!!.trim().toInt()

    val scores = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()

    val result = breakingRecords(scores)

    println(result.joinToString(" "))
}
