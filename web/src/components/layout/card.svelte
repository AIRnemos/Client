<script>
    let clazz = "";
    export {clazz as class}
</script>
<div class={"card " + clazz}>
    <slot></slot>
</div>

<style lang="sass">
@import '../../css/color'

.card
    background: $white 
    border-radius: 1rem
    padding: 2rem
    margin: 0.5rem
</style>