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

fun kangaroo(x1: Int, v1: Int, x2: Int, v2: Int): String {
    val jumps = (x2 - x1) / (v1 - v2)
    return if (jumps < 0) "NO" else "YES"
}

fun main(args: Array<String>) {
    val first_multiple_input = readLine()!!.trimEnd().split(" ")
    val x1 = first_multiple_input[0].toInt()
    val v1 = first_multiple_input[1].toInt()
    val x2 = first_multiple_input[2].toInt()
    val v2 = first_multiple_input[3].toInt()
    val result = kangaroo(x1, v1, x2, v2)
    println(result)
}
