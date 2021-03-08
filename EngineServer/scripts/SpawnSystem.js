function handleDeath(e, eventManager) {
    var gameObject = e.dyingObject;

    var spawnEvent = new SpawnEvent(gameObject);
    eventManager.raiseEvent(spawnEvent);
}