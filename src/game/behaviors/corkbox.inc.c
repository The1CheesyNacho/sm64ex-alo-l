// corkbox.inc.c
// TODO: This split seems weird. Investigate further?

void bhv_bobomb_bully_death_smoke_init(void) {
    o->oPosY -= 300.0f;

    cur_obj_scale(10.0f);
}

void bhv_bobomb_explosion_bubble_init(void) {
    obj_scale_xyz(o, 2.0f, 2.0f, 1.0f);

    o->oBobombExpBubGfxExpRateX = (s32)(random_float() * 2048.0f) + 0x800;
    o->oBobombExpBubGfxExpRateY = (s32)(random_float() * 2048.0f) + 0x800;
    o->oTimer = random_float() * 10.0f;
    o->oVelY = (s32)(random_float() * 4.0f) + 4;
}

void bhv_bobomb_explosion_bubble_loop(void) {
    f32 waterY = gMarioState->waterLevel;

    o->header.gfx.scale[0] = sins(o->oBobombExpBubGfxScaleFacX) * 0.5 + 2.0;
    o->oBobombExpBubGfxScaleFacX += o->oBobombExpBubGfxExpRateX;

    o->header.gfx.scale[1] = sins(o->oBobombExpBubGfxScaleFacY) * 0.5 + 2.0;
    o->oBobombExpBubGfxScaleFacY += o->oBobombExpBubGfxExpRateY;

    if (o->oPosY > waterY) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        o->oPosY += 5.0f;
        spawn_object(o, MODEL_SMALL_WATER_SPLASH, bhvObjectWaterSplash);
    }

    if (o->oTimer > 60) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    o->oPosY += o->oVelY;
    o->oTimer++;
}
