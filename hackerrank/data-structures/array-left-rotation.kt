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
import kotlin.math.abs

fun rotateLeft(d: Int, arr: Array<Int>): Array<Int> {
    val result = IntArray(arr.size)

    val arrSize = arr.size
    val rotation = d % arrSize
    for (index in arr.indices) {
        val nextIndex = index - rotation
        val finalIndex = if (nextIndex < 0) arrSize + nextIndex else nextIndex
        result[finalIndex] = arr[index]
    }
    return result.toTypedArray();
}

fun main(args: Array<String>) {
    val first_multiple_input = readLine()!!.trimEnd().split(" ")
    val n = first_multiple_input[0].toInt()
    val d = first_multiple_input[1].toInt()
    val arr = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val result = rotateLeft(d, arr)
    println(result.joinToString(" "))
}
