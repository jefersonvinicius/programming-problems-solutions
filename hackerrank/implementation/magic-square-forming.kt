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

// 1 1 1 -> 12
// 1 1 1 -> 12
// 1 1 1 -> 12

// 1 1 1 -> 1 9 5 -> 12
// 1 1 1 -> 2 6 7 -> 12
// 1 1 1 -> 3 4 8 -> 12

fun formingMagicSquare(s: Array<Array<Int>>): Int {
    columnsCost(s)
    return rowsCost(s)
}

fun sumArray(array: Array<Int>): Int {
    return array.fold(0) {
        total, current -> total + current
    }
}

fun rowsCost(square: Array<Array<Int>>): Int {
    var result = 0
    for (row in square) {
        val rowTotal = sumArray(row)
        result += cost(rowTotal)
    }
    return result;
}

fun columnsCost(square: Array<Array<Int>>): Int {
    var cols = arrayOf(0, 0, 0)
    for (row in square) {
        for ((index, col) in row.withIndex()) {
            cols[index] += col
        }
    }

    var result = cols.fold(0) {
        total, current -> total + cost(current)
    }

    for (c in cols) {
        println(c)
    }

    println("result: $result");

    return result;
}

fun cost(value: Int): Int {
    return Math.abs(value - 15)
}

fun main(args: Array<String>) {
    val s = Array<Array<Int>>(3, { Array<Int>(3, { 0 }) })
    for (i in 0 until 3) {
        s[i] = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    }
    val result = formingMagicSquare(s)
    println(result)
}
