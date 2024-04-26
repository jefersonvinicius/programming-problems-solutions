/**
 * Definition for singly-linked list.
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function addTwoNumbers(l1: ListNode | null, l2: ListNode | null): ListNode | null {
  let current1 = l1,
    current2 = l2;
  let onePassed = false;
  let current = null,
    firstNode = null;
  while (!!current1 || !!current2 || onePassed) {
    const initialNodeValue = (current1?.val ?? 0) + (current2?.val ?? 0) + (onePassed ? 1 : 0);
    onePassed = initialNodeValue > 9;
    const finalNodeValue = onePassed ? initialNodeValue - 10 : initialNodeValue;

    if (!current) current = new ListNode(finalNodeValue);
    else current.next = new ListNode(finalNodeValue);

    if (!firstNode) firstNode = current;

    if (current.next) current = current.next;
    current1 = current1?.next;
    current2 = current2?.next;
  }

  return firstNode;
}
