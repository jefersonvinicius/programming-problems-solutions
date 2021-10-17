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

fun hourglassSum(arr: Array<Array<Int>>): Int {
    var biggerHourglass = Int.MIN_VALUE;
    for (row in 0..3) {
        for (col in 0..3) {
            val sum = getHourglassSum(arr, row, col)
            biggerHourglass = if (sum > biggerHourglass) sum else biggerHourglass
        }
    }
    return biggerHourglass
}

fun getHourglassSum(arr: Array<Array<Int>>, initialRow: Int, initialColumn: Int): Int {
    val firstRowSum = arr[initialRow][initialColumn] + arr[initialRow][initialColumn + 1] + arr[initialRow][initialColumn + 2]
    val middleRowSum = arr[initialRow + 1][initialColumn + 1]
    val thirdRowSum = arr[initialRow + 2][initialColumn] + arr[initialRow + 2][initialColumn + 1] + arr[initialRow + 2][initialColumn + 2]
    return firstRowSum + middleRowSum + thirdRowSum

}

fun main(args: Array<String>) {

    val arr = Array<Array<Int>>(6, { Array<Int>(6, { 0 }) })

    for (i in 0 until 6) {
        arr[i] = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    }

    val result = hourglassSum(arr)

    println(result)
}
