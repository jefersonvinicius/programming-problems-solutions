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

fun sockMerchant(n: Int, socks: Array<Int>): Int {
    val socksAmount = mutableMapOf<Int, Int>()
    for (sock in socks) {
        if (!socksAmount.containsKey(sock)) socksAmount[sock] = 0
        socksAmount[sock] = socksAmount.getValue(sock) + 1
    }

    val result = socksAmount.values.fold(0) {
        total, current -> total + Math.floor(current / 2.0).toInt()
    }

    return result
}

fun main(args: Array<String>) {
    val n = readLine()!!.trim().toInt()
    val ar = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
    val result = sockMerchant(n, ar)
    println(result)
}
