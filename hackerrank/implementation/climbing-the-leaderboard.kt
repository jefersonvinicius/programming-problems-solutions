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
    var scores = createMappedScores(ranked)
    var scoresCresc = scores.keys.reversed()
    var initialPosition = ranked.size

    for (score in scoresCresc) {
        println(score)
    }

    return result.toTypedArray()
}


fun createMappedScores(ranking: Array<Int>): Map<Int, Int> {
    val pontuations = mutableMapOf<Int, Int>()
    for (score in ranking) {
        pontuations[score] = pontuations.getOrDefault(score, 0) + 1
    }
    return pontuations;
}

fun main(args: Array<String>) {
    val rankedCount = readLine()!!.trim().toInt()
    val ranked = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val playerCount = readLine()!!.trim().toInt()
    val player = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val result = climbingLeaderboard(ranked, player)
    println(result.joinToString("\n"))
}
