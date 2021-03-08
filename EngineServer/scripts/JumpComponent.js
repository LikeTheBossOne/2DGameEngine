function update(jumpComponent, moveComponent) {
    if (jumpComponent.shouldJump && !jumpComponent.isJumping) {
        moveComponent.velocityY = moveComponent.velocityY + jumpComponent.jumpAcceleration;

        jumpComponent.isJumping = true;
        jumpComponent.shouldJump = false;
    }
}