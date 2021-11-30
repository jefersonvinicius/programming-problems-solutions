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

fun pickingNumbers(array: Array<Int>): Int {
    var result = 0;
    for ((index) in array.withIndex()) {
        val subarray = createSubarrayFromIndex(array, index)
        if (subarray.size > result) result = subarray.size;
    }
    return result
}

fun createSubarrayFromIndex(array: Array<Int>, fromIndex: Int): Array<Int> {
    val valueFromIndex = array[fromIndex]
    var result = mutableListOf<Int>()
    for ((index, value) in array.withIndex()) {
        if (fromIndex == index) continue;
        if (hasAbsoluteDifference(value, valueFromIndex) && hasAbsoluteDifferenceInArray(value, result)) {
            if (result.isEmpty()) result.add(valueFromIndex)
            result.add(value)
        }
    }
    return result.toTypedArray()
}

fun hasAbsoluteDifferenceInArray(value: Int, array: MutableList<Int>): Boolean {
    for (number in array) {
        if (!hasAbsoluteDifference(value, number)) return false;
    }
    return true
}

fun hasAbsoluteDifference(a: Int, b: Int): Boolean {
    return Math.abs(a - b) <= 1
}

fun main(args: Array<String>) {
    val n = readLine()!!.trim().toInt()
    val a = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val result = pickingNumbers(a)
    println(result)
}
