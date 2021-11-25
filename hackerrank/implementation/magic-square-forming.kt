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

fun formingMagicSquare(s: Array<Array<Int>>): Int {
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
        result += Math.abs(rowTotal - 15)
    }
    return result;
}

//fun columnsCost(square: Array<Array<Int>>): Int {
//
//}


fun main(args: Array<String>) {
    val s = Array<Array<Int>>(3, { Array<Int>(3, { 0 }) })
    for (i in 0 until 3) {
        s[i] = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    }
    val result = formingMagicSquare(s)
    println(result)
}
