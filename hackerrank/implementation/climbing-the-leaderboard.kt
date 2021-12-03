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
    val result = mutableListOf<Int>()
    val positions = createPositions(ranked).reversed()
    positions.forEach { position -> println("${position.index} -> ${position.score}") }
    var playerScoreIndex = 0

    val scoresToIgnore = mutableMapOf<Int, Boolean>()
    for (position in positions) {
        if (playerScoreIndex == player.size) break;
        if (scoresToIgnore[position.score] == true) continue;

        val playerScore = player[playerScoreIndex]
        if (playerScore == position.score) {
            result.add(position.index)
        } else if (playerScore > position.score) {
            result.add(position.index - 1)
        } else if (playerScore < position.score) {
            result.add(position.index + 1)
        }
        playerScoreIndex++;
        scoresToIgnore[position.score] = true;
    }

    return result.toTypedArray()
}

data class Position (val index: Int, val score: Int) {}

fun createPositions(ranking: Array<Int>): Array<Position> {
    var position = 1
    val result = mutableListOf<Position>()
    for ((index, value) in ranking.withIndex()) {
        if (index == 0) {
            result.add(Position(index = position, score = value))
            continue;
        }

        if (value < ranking[index - 1]) position++;

        result.add(Position(index = position, score = value))
    }
    return result.toTypedArray()
}

fun main(args: Array<String>) {
    val rankedCount = readLine()!!.trim().toInt()
    val ranked = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val playerCount = readLine()!!.trim().toInt()
    val player = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val result = climbingLeaderboard(ranked, player)
    println(result.joinToString("\n"))
}
