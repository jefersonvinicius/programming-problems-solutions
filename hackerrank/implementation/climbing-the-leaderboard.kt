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

fun climbingLeaderboard(ranked: Array<Int>, player: Array<Int>): Array<Int> {
    var result = mutableListOf<Int>()
    val positions = createPositionsMap(ranked)
    for (score in player) {
        var index = ranked.indexOfLast { score < it  }
        if (index == -1) {
            result.add(1)
        } else {
            result.add(positions[index] + 1)
        }
    }
    return result.toTypedArray()
}

fun createPositionsMap(ranking: Array<Int>): Array<Int> {
    val result = Array(ranking.size) { -1 }
    var position = 1;
    for ((index, currentValue) in ranking.withIndex()) {
        if (index == 0) {
            result[index] = position
            continue
        }
        val previousValue = ranking[index - 1]
        if (currentValue < previousValue) position++

        result[index] = position
    }
    return result;
}

fun main(args: Array<String>) {
    val rankedCount = readLine()!!.trim().toInt()
    val ranked = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val playerCount = readLine()!!.trim().toInt()
    val player = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val result = climbingLeaderboard(ranked, player)
    println(result.joinToString("\n"))
}
