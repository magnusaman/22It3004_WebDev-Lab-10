function addItemController(item) {
    addItem(item);
    displayItems(getItemList());
}

function init() {
    const itemInput = document.getElementById("itemInput");
    itemInput.addEventListener("change", () => {
        addItemController(itemInput.value.trim());
        itemInput.value = "";
    });

    // Other initialization code
}

init();
