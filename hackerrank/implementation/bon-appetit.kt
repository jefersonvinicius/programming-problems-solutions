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

fun bonAppetit(bill: Array<Int>, notEatByAnna: Int, charged: Int): Unit {
    var total = 0;
    for ((index, value) in bill.withIndex()) {
        if (index == notEatByAnna) continue;
        total += value;
    }

    val chargedCorrect = total / 2
    if (charged == chargedCorrect) println("Bon Appetit")
    else println(charged - chargedCorrect)
}

fun main(args: Array<String>) {
    val first_multiple_input = readLine()!!.trimEnd().split(" ")
    val n = first_multiple_input[0].toInt()
    val k = first_multiple_input[1].toInt()
    val bill = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val b = readLine()!!.trim().toInt()
    bonAppetit(bill, k, b)
}
