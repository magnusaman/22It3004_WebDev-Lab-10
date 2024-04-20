function displayItems(itemList) {
    const itemListElement = document.getElementById("itemList");
    itemListElement.innerHTML = "";

    itemList.forEach(item => {
        const li = document.createElement("li");
        li.textContent = item;
        itemListElement.appendChild(li);
    });
}
