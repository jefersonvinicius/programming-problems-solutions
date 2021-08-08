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

fun dynamicArray(n: Int, queries: Array<Array<Int>>): Array<Int> {
    val answer = mutableListOf<Int>()
    var array = Array(n) { mutableListOf<Int>() }

    var lastAnswer = 0
    for (query in queries) {
        val x = query[1]
        val y = query[2]

        if (query[0] == 1) {
            val idx = ((x xor lastAnswer) % n)
            array[idx].add(y)
        }

        if (query[0] == 2) {
            val idx = ((x xor lastAnswer) % n)
            lastAnswer = array[idx][y % array[idx].size]
            answer.add(lastAnswer)
        }
    }
    return answer.toTypedArray()
}

fun main(args: Array<String>) {
    val first_multiple_input = readLine()!!.trimEnd().split(" ")
    val n = first_multiple_input[0].toInt()
    val q = first_multiple_input[1].toInt()
    val queries = Array<Array<Int>>(q, { Array<Int>(3, { 0 }) })
    for (i in 0 until q) {
        queries[i] = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    }
    val result = dynamicArray(n, queries)
    println(result.joinToString("\n"))
}
