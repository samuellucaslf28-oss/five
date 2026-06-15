#pragma once
#pragma region Enums
enum BoneMasks : int { SKEL_ROOT = 0x0, SKEL_Pelvis = 0x2e28, SKEL_L_Thigh = 0xe39f, SKEL_L_Calf = 0xf9bb, SKEL_L_Foot = 0x3779, SKEL_L_Toe0 = 0x83c, IK_L_Foot = 0xfedd, PH_L_Foot = 0xe175, MH_L_Knee = 0xb3fe, SKEL_R_Thigh = 0xca72, SKEL_R_Calf = 0x9000, SKEL_R_Foot = 0xcc4d, SKEL_R_Toe0 = 0x512d, IK_R_Foot = 0x8aae, PH_R_Foot = 0x60e6, MH_R_Knee = 0x3fcf, RB_L_ThighRoll = 0x5c57, RB_R_ThighRoll = 0x192a, SKEL_Spine_Root = 0xe0fd, SKEL_Spine0 = 0x5c01, SKEL_Spine1 = 0x60f0, SKEL_Spine2 = 0x60f1, SKEL_Spine3 = 0x60f2, SKEL_L_Clavicle = 0xfcd9, SKEL_L_UpperArm = 0xb1c5, SKEL_L_Forearm = 0xeeeb, SKEL_L_Hand = 0x49d9, SKEL_L_Finger00 = 0x67f2, SKEL_L_Finger01 = 0xff9, SKEL_L_Finger02 = 0xffa, SKEL_L_Finger10 = 0x67f3, SKEL_L_Finger11 = 0x1049, SKEL_L_Finger12 = 0x104a, SKEL_L_Finger20 = 0x67f4, SKEL_L_Finger21 = 0x1059, SKEL_L_Finger22 = 0x105a, SKEL_L_Finger30 = 0x67f5, SKEL_L_Finger31 = 0x1029, SKEL_L_Finger32 = 0x102a, SKEL_L_Finger40 = 0x67f6, SKEL_L_Finger41 = 0x1039, SKEL_L_Finger42 = 0x103a, PH_L_Hand = 0xeb95, IK_L_Hand = 0x8cbd, RB_L_ForeArmRoll = 0xee4f, RB_L_ArmRoll = 0x1470, MH_L_Elbow = 0x58b7, SKEL_R_Clavicle = 0x29d2, SKEL_R_UpperArm = 0x9d4d, SKEL_R_Forearm = 0x6e5c, SKEL_R_Hand = 0xdead, SKEL_R_Finger00 = 0xe5f2, SKEL_R_Finger01 = 0xfa10, SKEL_R_Finger02 = 0xfa11, SKEL_R_Finger10 = 0xe5f3, SKEL_R_Finger11 = 0xfa60, SKEL_R_Finger12 = 0xfa61, SKEL_R_Finger20 = 0xe5f4, SKEL_R_Finger21 = 0xfa70, SKEL_R_Finger22 = 0xfa71, SKEL_R_Finger30 = 0xe5f5, SKEL_R_Finger31 = 0xfa40, SKEL_R_Finger32 = 0xfa41, SKEL_R_Finger40 = 0xe5f6, SKEL_R_Finger41 = 0xfa50, SKEL_R_Finger42 = 0xfa51, PH_R_Hand = 0x6f06, IK_R_Hand = 0x188e, RB_R_ForeArmRoll = 0xab22, RB_R_ArmRoll = 0x90ff, MH_R_Elbow = 0xbb0, SKEL_Neck_1 = 0x9995, SKEL_Head = 0x796e, IK_Head = 0x322c, FACIAL_facialRoot = 0xfe2c, FB_L_Brow_Out_000 = 0xe3db, FB_L_Lid_Upper_000 = 0xb2b6, FB_L_Eye_000 = 0x62ac, FB_L_CheekBone_000 = 0x542e, FB_L_Lip_Corner_000 = 0x74ac, FB_R_Lid_Upper_000 = 0xaa10, FB_R_Eye_000 = 0x6b52, FB_R_CheekBone_000 = 0x4b88, FB_R_Brow_Out_000 = 0x54c, FB_R_Lip_Corner_000 = 0x2ba6, FB_Brow_Centre_000 = 0x9149, FB_UpperLipRoot_000 = 0x4ed2, FB_UpperLip_000 = 0xf18f, FB_L_Lip_Top_000 = 0x4f37, FB_R_Lip_Top_000 = 0x4537, FB_Jaw_000 = 0xb4a0, FB_LowerLipRoot_000 = 0x4324, FB_LowerLip_000 = 0x508f, FB_L_Lip_Bot_000 = 0xb93b, FB_R_Lip_Bot_000 = 0xc33b, FB_Tongue_000 = 0xb987, RB_Neck_1 = 0x8b93, IK_Root = 0xdd1c };
enum ePedConfigFlags
{
	CPED_CONFIG_FLAG_CreatedByFactory = 0,
	CPED_CONFIG_FLAG_CanBeShotInVehicle = 1,
	CPED_CONFIG_FLAG_NoCriticalHits, // Detected by AC
	CPED_CONFIG_FLAG_DrownsInWater,
	CPED_CONFIG_FLAG_DrownsInSinkingVehicle,
	CPED_CONFIG_FLAG_DiesInstantlyWhenSwimming,
	CPED_CONFIG_FLAG_HasBulletProofVest,
	CPED_CONFIG_FLAG_UpperBodyDamageAnimsOnly,
	CPED_CONFIG_FLAG_NeverFallOffSkis,
	CPED_CONFIG_FLAG_NeverEverTargetThisPed,
	CPED_CONFIG_FLAG_ThisPedIsATargetPriority,
	CPED_CONFIG_FLAG_TargettableWithNoLos,
	CPED_CONFIG_FLAG_DoesntListenToPlayerGroupCommands,
	CPED_CONFIG_FLAG_NeverLeavesGroup,
	CPED_CONFIG_FLAG_DoesntDropWeaponsWhenDead,
	CPED_CONFIG_FLAG_SetDelayedWeaponAsCurrent,
	CPED_CONFIG_FLAG_KeepTasksAfterCleanUp,
	CPED_CONFIG_FLAG_BlockNonTemporaryEvents,
	CPED_CONFIG_FLAG_HasAScriptBrain,
	CPED_CONFIG_FLAG_WaitingForScriptBrainToLoad,
	CPED_CONFIG_FLAG_AllowMedicsToReviveMe,
	CPED_CONFIG_FLAG_MoneyHasBeenGivenByScript,
	CPED_CONFIG_FLAG_NotAllowedToCrouch,
	CPED_CONFIG_FLAG_DeathPickupsPersist,
	CPED_CONFIG_FLAG_IgnoreSeenMelee,
	CPED_CONFIG_FLAG_ForceDieIfInjured,
	CPED_CONFIG_FLAG_DontDragMeOutCar,
	CPED_CONFIG_FLAG_StayInCarOnJack,
	CPED_CONFIG_FLAG_ForceDieInCar, // prae
	CPED_CONFIG_FLAG_GetOutUndriveableVehicle,
	CPED_CONFIG_FLAG_WillRemainOnBoatAfterMissionEnds,
	CPED_CONFIG_FLAG_DontStoreAsPersistent,
	CPED_CONFIG_FLAG_WillFlyThroughWindscreen,
	CPED_CONFIG_FLAG_DieWhenRagdoll,
	CPED_CONFIG_FLAG_HasHelmet,
	CPED_CONFIG_FLAG_UseHelmet,
	CPED_CONFIG_FLAG_DontTakeOffHelmet,
	CPED_CONFIG_FLAG_HideInCutscene,
	CPED_CONFIG_FLAG_PedIsEnemyToPlayer,
	CPED_CONFIG_FLAG_DisableEvasiveDives,
	CPED_CONFIG_FLAG_PedGeneratesDeadBodyEvents,
	CPED_CONFIG_FLAG_DontAttackPlayerWithoutWantedLevel,
	CPED_CONFIG_FLAG_DontInfluenceWantedLevel,
	CPED_CONFIG_FLAG_DisablePlayerLockon,
	CPED_CONFIG_FLAG_DisableLockonToRandomPeds,
	CPED_CONFIG_FLAG_AllowLockonToFriendlyPlayers,
	CPED_CONFIG_FLAG_DisableHornAudioWhenDead,
	CPED_CONFIG_FLAG_PedBeingDeleted,
	CPED_CONFIG_FLAG_BlockWeaponSwitching,
	CPED_CONFIG_FLAG_BlockGroupPedAimedAtResponse,
	CPED_CONFIG_FLAG_WillFollowLeaderAnyMeans,
	CPED_CONFIG_FLAG_BlippedByScript,
	CPED_CONFIG_FLAG_DrawRadarVisualField,
	CPED_CONFIG_FLAG_StopWeaponFiringOnImpact,
	CPED_CONFIG_FLAG_DissableAutoFallOffTests,
	CPED_CONFIG_FLAG_SteerAroundDeadBodies,
	CPED_CONFIG_FLAG_ConstrainToNavMesh,
	CPED_CONFIG_FLAG_SyncingAnimatedProps,
	CPED_CONFIG_FLAG_IsFiring,
	CPED_CONFIG_FLAG_WasFiring,
	CPED_CONFIG_FLAG_IsStanding,
	CPED_CONFIG_FLAG_WasStanding,
	CPED_CONFIG_FLAG_InVehicle,
	CPED_CONFIG_FLAG_OnMount,
	CPED_CONFIG_FLAG_AttachedToVehicle,
	CPED_CONFIG_FLAG_IsSwimming,
	CPED_CONFIG_FLAG_WasSwimming,
	CPED_CONFIG_FLAG_IsSkiing,
	CPED_CONFIG_FLAG_IsSitting,
	CPED_CONFIG_FLAG_KilledByStealth,
	CPED_CONFIG_FLAG_KilledByTakedown,
	CPED_CONFIG_FLAG_Knockedout,
	CPED_CONFIG_FLAG_ClearRadarBlipOnDeath,
	CPED_CONFIG_FLAG_JustGotOffTrain,
	CPED_CONFIG_FLAG_JustGotOnTrain,
	CPED_CONFIG_FLAG_UsingCoverPoint,
	CPED_CONFIG_FLAG_IsInTheAir,
	CPED_CONFIG_FLAG_KnockedUpIntoAir,
	CPED_CONFIG_FLAG_IsAimingGun,
	CPED_CONFIG_FLAG_HasJustLeftCar,
	CPED_CONFIG_FLAG_TargetWhenInjuredAllowed,
	CPED_CONFIG_FLAG_CurrLeftFootCollNM,
	CPED_CONFIG_FLAG_PrevLeftFootCollNM,
	CPED_CONFIG_FLAG_CurrRightFootCollNM,
	CPED_CONFIG_FLAG_PrevRightFootCollNM,
	CPED_CONFIG_FLAG_HasBeenBumpedInCar,
	CPED_CONFIG_FLAG_InWaterTaskQuitToClimbLadder,
	CPED_CONFIG_FLAG_NMTwoHandedWeaponBothHandsConstrained,
	CPED_CONFIG_FLAG_CreatedBloodPoolTimer,
	CPED_CONFIG_FLAG_DontActivateRagdollFromAnyPedImpact,
	CPED_CONFIG_FLAG_GroupPedFailedToEnterCover,
	CPED_CONFIG_FLAG_AlreadyChattedOnPhone,
	CPED_CONFIG_FLAG_AlreadyReactedToPedOnRoof,
	CPED_CONFIG_FLAG_ForcePedLoadCover,
	CPED_CONFIG_FLAG_BlockCoweringInCover,
	CPED_CONFIG_FLAG_BlockPeekingInCover,
	CPED_CONFIG_FLAG_JustLeftCarNotCheckedForDoors,
	CPED_CONFIG_FLAG_VaultFromCover,
	CPED_CONFIG_FLAG_AutoConversationLookAts,
	CPED_CONFIG_FLAG_UsingCrouchedPedCapsule,
	CPED_CONFIG_FLAG_HasDeadPedBeenReported,
	CPED_CONFIG_FLAG_ForcedAim,
	CPED_CONFIG_FLAG_SteersAroundPeds,
	CPED_CONFIG_FLAG_SteersAroundObjects,
	CPED_CONFIG_FLAG_OpenDoorArmIK,
	CPED_CONFIG_FLAG_ForceReload,
	CPED_CONFIG_FLAG_DontActivateRagdollFromVehicleImpact,
	CPED_CONFIG_FLAG_DontActivateRagdollFromBulletImpact,
	CPED_CONFIG_FLAG_DontActivateRagdollFromExplosions,
	CPED_CONFIG_FLAG_DontActivateRagdollFromFire,
	CPED_CONFIG_FLAG_DontActivateRagdollFromElectrocution,
	CPED_CONFIG_FLAG_IsBeingDraggedToSafety,
	CPED_CONFIG_FLAG_HasBeenDraggedToSafety,
	CPED_CONFIG_FLAG_KeepWeaponHolsteredUnlessFired,
	CPED_CONFIG_FLAG_ForceScriptControlledKnockout,
	CPED_CONFIG_FLAG_FallOutOfVehicleWhenKilled,
	CPED_CONFIG_FLAG_GetOutBurningVehicle,
	CPED_CONFIG_FLAG_BumpedByPlayer,
	CPED_CONFIG_FLAG_RunFromFiresAndExplosions,
	CPED_CONFIG_FLAG_TreatAsPlayerDuringTargeting,
	CPED_CONFIG_FLAG_IsHandCuffed,
	CPED_CONFIG_FLAG_IsAnkleCuffed,
	CPED_CONFIG_FLAG_DisableMelee,
	CPED_CONFIG_FLAG_DisableUnarmedDrivebys,
	CPED_CONFIG_FLAG_JustGetsPulledOutWhenElectrocuted,
	CPED_CONFIG_FLAG_UNUSED_REPLACE_ME,
	CPED_CONFIG_FLAG_WillNotHotwireLawEnforcementVehicle,
	CPED_CONFIG_FLAG_WillCommandeerRatherThanJack,
	CPED_CONFIG_FLAG_CanBeAgitated,
	CPED_CONFIG_FLAG_ForcePedToFaceLeftInCover,
	CPED_CONFIG_FLAG_ForcePedToFaceRightInCover,
	CPED_CONFIG_FLAG_BlockPedFromTurningInCover,
	CPED_CONFIG_FLAG_KeepRelationshipGroupAfterCleanUp,
	CPED_CONFIG_FLAG_ForcePedToBeDragged,
	CPED_CONFIG_FLAG_PreventPedFromReactingToBeingJacked,
	CPED_CONFIG_FLAG_IsScuba,
	CPED_CONFIG_FLAG_WillArrestRatherThanJack,
	CPED_CONFIG_FLAG_RemoveDeadExtraFarAway,
	CPED_CONFIG_FLAG_RidingTrain,
	CPED_CONFIG_FLAG_ArrestResult,
	CPED_CONFIG_FLAG_CanAttackFriendly,
	CPED_CONFIG_FLAG_WillJackAnyPlayer,
	CPED_CONFIG_FLAG_BumpedByPlayerVehicle,
	CPED_CONFIG_FLAG_DodgedPlayerVehicle,
	CPED_CONFIG_FLAG_WillJackWantedPlayersRatherThanStealCar,
	CPED_CONFIG_FLAG_NoCopWantedAggro,
	CPED_CONFIG_FLAG_DisableLadderClimbing,
	CPED_CONFIG_FLAG_StairsDetected,
	CPED_CONFIG_FLAG_SlopeDetected,
	CPED_CONFIG_FLAG_HelmetHasBeenShot,
	CPED_CONFIG_FLAG_CowerInsteadOfFlee,
	CPED_CONFIG_FLAG_CanActivateRagdollWhenVehicleUpsideDown,
	CPED_CONFIG_FLAG_AlwaysRespondToCriesForHelp,
	CPED_CONFIG_FLAG_DisableBloodPoolCreation,
	CPED_CONFIG_FLAG_ShouldFixIfNoCollision,
	CPED_CONFIG_FLAG_CanPerformArrest,
	CPED_CONFIG_FLAG_CanPerformUncuff,
	CPED_CONFIG_FLAG_CanBeArrested,
	CPED_CONFIG_FLAG_MoverConstrictedByOpposingCollisions,
	CPED_CONFIG_FLAG_PlayerPreferFrontSeatMP,
	CPED_CONFIG_FLAG_DontActivateRagdollFromImpactObject,
	CPED_CONFIG_FLAG_DontActivateRagdollFromMelee,
	CPED_CONFIG_FLAG_DontActivateRagdollFromWaterJet,
	CPED_CONFIG_FLAG_DontActivateRagdollFromDrowning,
	CPED_CONFIG_FLAG_DontActivateRagdollFromFalling,
	CPED_CONFIG_FLAG_DontActivateRagdollFromRubberBullet,
	CPED_CONFIG_FLAG_IsInjured,
	CPED_CONFIG_FLAG_DontEnterVehiclesInPlayersGroup,
	CPED_CONFIG_FLAG_SwimmingTasksRunning,
	CPED_CONFIG_FLAG_PreventAllMeleeTaunts,
	CPED_CONFIG_FLAG_ForceDirectEntry,
	CPED_CONFIG_FLAG_AlwaysSeeApproachingVehicles,
	CPED_CONFIG_FLAG_CanDiveAwayFromApproachingVehicles,
	CPED_CONFIG_FLAG_AllowPlayerToInterruptVehicleEntryExit,
	CPED_CONFIG_FLAG_OnlyAttackLawIfPlayerIsWanted,
	CPED_CONFIG_FLAG_PlayerInContactWithKinematicPed,
	CPED_CONFIG_FLAG_PlayerInContactWithSomethingOtherThanKinematicPed,
	CPED_CONFIG_FLAG_PedsJackingMeDontGetIn,
	CPED_CONFIG_FLAG_AdditionalRappellingPed,
	CPED_CONFIG_FLAG_PedIgnoresAnimInterruptEvents,
	CPED_CONFIG_FLAG_IsInCustody,
	CPED_CONFIG_FLAG_ForceStandardBumpReactionThresholds,
	CPED_CONFIG_FLAG_LawWillOnlyAttackIfPlayerIsWanted,
	CPED_CONFIG_FLAG_IsAgitated,
	CPED_CONFIG_FLAG_PreventAutoShuffleToDriversSeat,
	CPED_CONFIG_FLAG_UseKinematicModeWhenStationary,
	CPED_CONFIG_FLAG_EnableWeaponBlocking,
	CPED_CONFIG_FLAG_HasHurtStarted,
	CPED_CONFIG_FLAG_DisableHurt,
	CPED_CONFIG_FLAG_PlayerIsWeird,
	CPED_CONFIG_FLAG_PedHadPhoneConversation,
	CPED_CONFIG_FLAG_BeganCrossingRoad,
	CPED_CONFIG_FLAG_WarpIntoLeadersVehicle,
	CPED_CONFIG_FLAG_DoNothingWhenOnFootByDefault,
	CPED_CONFIG_FLAG_UsingScenario,
	CPED_CONFIG_FLAG_VisibleOnScreen,
	CPED_CONFIG_FLAG_DontCollideWithKinematic,
	CPED_CONFIG_FLAG_ActivateOnSwitchFromLowPhysicsLod,
	CPED_CONFIG_FLAG_DontActivateRagdollOnPedCollisionWhenDead,
	CPED_CONFIG_FLAG_DontActivateRagdollOnVehicleCollisionWhenDead,
	CPED_CONFIG_FLAG_HasBeenInArmedCombat,
	CPED_CONFIG_FLAG_UseDiminishingAmmoRate,
	CPED_CONFIG_FLAG_Avoidance_Ignore_All,
	CPED_CONFIG_FLAG_Avoidance_Ignored_by_All,
	CPED_CONFIG_FLAG_Avoidance_Ignore_Group1,
	CPED_CONFIG_FLAG_Avoidance_Member_of_Group1,
	CPED_CONFIG_FLAG_ForcedToUseSpecificGroupSeatIndex,
	CPED_CONFIG_FLAG_LowPhysicsLodMayPlaceOnNavMesh,
	CPED_CONFIG_FLAG_DisableExplosionReactions,
	CPED_CONFIG_FLAG_DodgedPlayer,
	CPED_CONFIG_FLAG_WaitingForPlayerControlInterrupt,
	CPED_CONFIG_FLAG_ForcedToStayInCover,
	CPED_CONFIG_FLAG_GeneratesSoundEvents,
	CPED_CONFIG_FLAG_ListensToSoundEvents,
	CPED_CONFIG_FLAG_AllowToBeTargetedInAVehicle,
	CPED_CONFIG_FLAG_WaitForDirectEntryPointToBeFreeWhenExiting,
	CPED_CONFIG_FLAG_OnlyRequireOnePressToExitVehicle,
	CPED_CONFIG_FLAG_ForceExitToSkyDive,
	CPED_CONFIG_FLAG_SteersAroundVehicles,
	CPED_CONFIG_FLAG_AllowPedInVehiclesOverrideTaskFlags,
	CPED_CONFIG_FLAG_DontEnterLeadersVehicle,
	CPED_CONFIG_FLAG_DisableExitToSkyDive,
	CPED_CONFIG_FLAG_ScriptHasDisabledCollision,
	CPED_CONFIG_FLAG_UseAmbientModelScaling,
	CPED_CONFIG_FLAG_DontWatchFirstOnNextHurryAway,
	CPED_CONFIG_FLAG_DisablePotentialToBeWalkedIntoResponse,
	CPED_CONFIG_FLAG_DisablePedAvoidance,
	CPED_CONFIG_FLAG_ForceRagdollUponDeath,
	CPED_CONFIG_FLAG_CanLosePropsOnDamage,
	CPED_CONFIG_FLAG_DisablePanicInVehicle,
	CPED_CONFIG_FLAG_AllowedToDetachTrailer,
	CPED_CONFIG_FLAG_HasShotBeenReactedToFromFront,
	CPED_CONFIG_FLAG_HasShotBeenReactedToFromBack,
	CPED_CONFIG_FLAG_HasShotBeenReactedToFromLeft,
	CPED_CONFIG_FLAG_HasShotBeenReactedToFromRight,
	CPED_CONFIG_FLAG_AllowBlockDeadPedRagdollActivation,
	CPED_CONFIG_FLAG_IsHoldingProp,
	CPED_CONFIG_FLAG_BlocksPathingWhenDead,
	CPED_CONFIG_FLAG_ForcePlayNormalScenarioExitOnNextScriptCommand,
	CPED_CONFIG_FLAG_ForcePlayImmediateScenarioExitOnNextScriptCommand,
	CPED_CONFIG_FLAG_ForceSkinCharacterCloth,
	CPED_CONFIG_FLAG_LeaveEngineOnWhenExitingVehicles,
	CPED_CONFIG_FLAG_PhoneDisableTextingAnimations,
	CPED_CONFIG_FLAG_PhoneDisableTalkingAnimations,
	CPED_CONFIG_FLAG_PhoneDisableCameraAnimations,
	CPED_CONFIG_FLAG_DisableBlindFiringInShotReactions,
	CPED_CONFIG_FLAG_AllowNearbyCoverUsage,
	CPED_CONFIG_FLAG_InStrafeTransition,
	CPED_CONFIG_FLAG_CanPlayInCarIdles,
	CPED_CONFIG_FLAG_CanAttackNonWantedPlayerAsLaw,
	CPED_CONFIG_FLAG_WillTakeDamageWhenVehicleCrashes,
	CPED_CONFIG_FLAG_AICanDrivePlayerAsRearPassenger,
	CPED_CONFIG_FLAG_PlayerCanJackFriendlyPlayers,
	CPED_CONFIG_FLAG_OnStairs,
	CPED_CONFIG_FLAG_SimulatingAiming,
	CPED_CONFIG_FLAG_AIDriverAllowFriendlyPassengerSeatEntry,
	CPED_CONFIG_FLAG_ParentCarIsBeingRemoved,
	CPED_CONFIG_FLAG_AllowMissionPedToUseInjuredMovement,
	CPED_CONFIG_FLAG_CanLoseHelmetOnDamage,
	CPED_CONFIG_FLAG_NeverDoScenarioExitProbeChecks,
	CPED_CONFIG_FLAG_SuppressLowLODRagdollSwitchWhenCorpseSettles,
	CPED_CONFIG_FLAG_PreventUsingLowerPrioritySeats,
	CPED_CONFIG_FLAG_JustLeftVehicleNeedsReset,
	CPED_CONFIG_FLAG_TeleportIfCantReachPlayer,
	CPED_CONFIG_FLAG_PedsInVehiclePositionNeedsReset,
	CPED_CONFIG_FLAG_PedsFullyInSeat,
	CPED_CONFIG_FLAG_AllowPlayerLockOnIfFriendly,
	CPED_CONFIG_FLAG_UseCameraHeadingForDesiredDirectionLockOnTest,
	CPED_CONFIG_FLAG_TeleportToLeaderVehicle,
	CPED_CONFIG_FLAG_Avoidance_Ignore_WeirdPedBuffer,
	CPED_CONFIG_FLAG_OnStairSlope,
	CPED_CONFIG_FLAG_HasPlayedNMGetup,
	CPED_CONFIG_FLAG_DontBlipCop,
	CPED_CONFIG_FLAG_SpawnedAtExtendedRangeScenario,
	CPED_CONFIG_FLAG_WalkAlongsideLeaderWhenClose,
	CPED_CONFIG_FLAG_KillWhenTrapped,
	CPED_CONFIG_FLAG_EdgeDetected,
	CPED_CONFIG_FLAG_AlwaysWakeUpPhysicsOfIntersectedPeds,
	CPED_CONFIG_FLAG_EquippedAmbientLoadOutWeapon,
	CPED_CONFIG_FLAG_AvoidTearGas,
	CPED_CONFIG_FLAG_StoppedSpeechUponFreezing,
	CPED_CONFIG_FLAG_DisableGoToWritheWhenInjured,
	CPED_CONFIG_FLAG_OnlyUseForcedSeatWhenEnteringHeliInGroup,
	CPED_CONFIG_FLAG_ThrownFromVehicleDueToExhaustion,
	CPED_CONFIG_FLAG_UpdateEnclosedSearchRegion,
	CPED_CONFIG_FLAG_DisableWeirdPedEvents,
	CPED_CONFIG_FLAG_ShouldChargeNow,
	CPED_CONFIG_FLAG_RagdollingOnBoat,
	CPED_CONFIG_FLAG_HasBrandishedWeapon,
	CPED_CONFIG_FLAG_AllowMinorReactionsAsMissionPed,
	CPED_CONFIG_FLAG_BlockDeadBodyShockingEventsWhenDead,
	CPED_CONFIG_FLAG_PedHasBeenSeen,
	CPED_CONFIG_FLAG_PedIsInReusePool,
	CPED_CONFIG_FLAG_PedWasReused,
	CPED_CONFIG_FLAG_DisableShockingEvents,
	CPED_CONFIG_FLAG_MovedUsingLowLodPhysicsSinceLastActive,
	CPED_CONFIG_FLAG_NeverReactToPedOnRoof,
	CPED_CONFIG_FLAG_ForcePlayFleeScenarioExitOnNextScriptCommand,
	CPED_CONFIG_FLAG_JustBumpedIntoVehicle,
	CPED_CONFIG_FLAG_DisableShockingDrivingOnPavementEvents,
	CPED_CONFIG_FLAG_ShouldThrowSmokeNow,
	CPED_CONFIG_FLAG_DisablePedConstraints,
	CPED_CONFIG_FLAG_ForceInitialPeekInCover,
	CPED_CONFIG_FLAG_CreatedByDispatch,
	CPED_CONFIG_FLAG_PointGunLeftHandSupporting,
	CPED_CONFIG_FLAG_DisableJumpingFromVehiclesAfterLeader,
	CPED_CONFIG_FLAG_DontActivateRagdollFromPlayerPedImpact,
	CPED_CONFIG_FLAG_DontActivateRagdollFromAiRagdollImpact,
	CPED_CONFIG_FLAG_DontActivateRagdollFromPlayerRagdollImpact,
	CPED_CONFIG_FLAG_DisableQuadrupedSpring,
	CPED_CONFIG_FLAG_IsInCluster,
	CPED_CONFIG_FLAG_ShoutToGroupOnPlayerMelee,
	CPED_CONFIG_FLAG_IgnoredByAutoOpenDoors,
	CPED_CONFIG_FLAG_PreferInjuredGetup,
	CPED_CONFIG_FLAG_ForceIgnoreMeleeActiveCombatant,
	CPED_CONFIG_FLAG_CheckLoSForSoundEvents,
	CPED_CONFIG_FLAG_JackedAbandonedCar,
	CPED_CONFIG_FLAG_CanSayFollowedByPlayerAudio,
	CPED_CONFIG_FLAG_ActivateRagdollFromMinorPlayerContact,
	CPED_CONFIG_FLAG_HasPortablePickupAttached,
	CPED_CONFIG_FLAG_ForcePoseCharacterCloth,
	CPED_CONFIG_FLAG_HasClothCollisionBounds,
	CPED_CONFIG_FLAG_HasHighHeels,
	CPED_CONFIG_FLAG_TreatAsAmbientPedForDriverLockOn,
	CPED_CONFIG_FLAG_DontBehaveLikeLaw,
	CPED_CONFIG_FLAG_SpawnedAtScenario,
	CPED_CONFIG_FLAG_DisablePoliceInvestigatingBody,
	CPED_CONFIG_FLAG_DisableWritheShootFromGround,
	CPED_CONFIG_FLAG_LowerPriorityOfWarpSeats,
	CPED_CONFIG_FLAG_DisableTalkTo,
	CPED_CONFIG_FLAG_DontBlip,
	CPED_CONFIG_FLAG_IsSwitchingWeapon,
	CPED_CONFIG_FLAG_IgnoreLegIkRestrictions,
	CPED_CONFIG_FLAG_ScriptForceNoTimesliceIntelligenceUpdate,
	CPED_CONFIG_FLAG_JackedOutOfMyVehicle,
	CPED_CONFIG_FLAG_WentIntoCombatAfterBeingJacked,
	CPED_CONFIG_FLAG_DontActivateRagdollForVehicleGrab,
	CPED_CONFIG_FLAG_ForcePackageCharacterCloth,
	CPED_CONFIG_FLAG_DontRemoveWithValidOrder,
	CPED_CONFIG_FLAG_AllowTaskDoNothingTimeslicing,
	CPED_CONFIG_FLAG_ForcedToStayInCoverDueToPlayerSwitch,
	CPED_CONFIG_FLAG_ForceProneCharacterCloth,
	CPED_CONFIG_FLAG_NotAllowedToJackAnyPlayers,
	CPED_CONFIG_FLAG_InToStrafeTransition,
	CPED_CONFIG_FLAG_KilledByStandardMelee,
	CPED_CONFIG_FLAG_AlwaysLeaveTrainUponArrival,
	CPED_CONFIG_FLAG_ForcePlayDirectedNormalScenarioExitOnNextScriptCommand,
	CPED_CONFIG_FLAG_OnlyWritheFromWeaponDamage,
	CPED_CONFIG_FLAG_UseSloMoBloodVfx,
	CPED_CONFIG_FLAG_EquipJetpack,
	CPED_CONFIG_FLAG_PreventDraggedOutOfCarThreatResponse,
	CPED_CONFIG_FLAG_ScriptHasCompletelyDisabledCollision,
	CPED_CONFIG_FLAG_NeverDoScenarioNavChecks,
	CPED_CONFIG_FLAG_ForceSynchronousScenarioExitChecking,
	CPED_CONFIG_FLAG_ThrowingGrenadeWhileAiming,
	CPED_CONFIG_FLAG_HeadbobToRadioEnabled,
	CPED_CONFIG_FLAG_ForceDeepSurfaceCheck,
	CPED_CONFIG_FLAG_DisableDeepSurfaceAnims,
	CPED_CONFIG_FLAG_DontBlipNotSynced,
	CPED_CONFIG_FLAG_IsDuckingInVehicle,
	CPED_CONFIG_FLAG_PreventAutoShuffleToTurretSeat,
	CPED_CONFIG_FLAG_DisableEventInteriorStatusCheck,
	CPED_CONFIG_FLAG_HasReserveParachute,
	CPED_CONFIG_FLAG_UseReserveParachute,
	CPED_CONFIG_FLAG_TreatDislikeAsHateWhenInCombat,
	CPED_CONFIG_FLAG_OnlyUpdateTargetWantedIfSeen,
	CPED_CONFIG_FLAG_AllowAutoShuffleToDriversSeat,
	CPED_CONFIG_FLAG_DontActivateRagdollFromSmokeGrenade,
	CPED_CONFIG_FLAG_LinkMBRToOwnerOnChain,
	CPED_CONFIG_FLAG_AmbientFriendBumpedByPlayer,
	CPED_CONFIG_FLAG_AmbientFriendBumpedByPlayerVehicle,
	CPED_CONFIG_FLAG_InFPSUnholsterTransition,
	CPED_CONFIG_FLAG_PreventReactingToSilencedCloneBullets,
	CPED_CONFIG_FLAG_DisableInjuredCryForHelpEvents,
	CPED_CONFIG_FLAG_NeverLeaveTrain,
	CPED_CONFIG_FLAG_DontDropJetpackOnDeath,
	CPED_CONFIG_FLAG_UseFPSUnholsterTransitionDuringCombatRoll,
	CPED_CONFIG_FLAG_ExitingFPSCombatRoll,
	CPED_CONFIG_FLAG_ScriptHasControlOfPlayer,
	CPED_CONFIG_FLAG_PlayFPSIdleFidgetsForProjectile,
	CPED_CONFIG_FLAG_DisableAutoEquipHelmetsInBikes,
	CPED_CONFIG_FLAG_DisableAutoEquipHelmetsInAircraft,
	CPED_CONFIG_FLAG_WasPlayingFPSGetup,
	CPED_CONFIG_FLAG_WasPlayingFPSMeleeActionResult,
	CPED_CONFIG_FLAG_PreferNoPriorityRemoval,
	CPED_CONFIG_FLAG_FPSFidgetsAbortedOnFire,
	CPED_CONFIG_FLAG_ForceFPSIKWithUpperBodyAnim,
	CPED_CONFIG_FLAG_SwitchingCharactersInFirstPerson,
	CPED_CONFIG_FLAG_IsClimbingLadder,
	CPED_CONFIG_FLAG_HasBareFeet,
	CPED_CONFIG_FLAG_UNUSED_REPLACE_ME_2,
	CPED_CONFIG_FLAG_GoOnWithoutVehicleIfItIsUnableToGetBackToRoad,
	CPED_CONFIG_FLAG_BlockDroppingHealthSnacksOnDeath,
	CPED_CONFIG_FLAG_ResetLastVehicleOnVehicleExit,
	CPED_CONFIG_FLAG_ForceThreatResponseToNonFriendToFriendMeleeActions,
	CPED_CONFIG_FLAG_DontRespondToRandomPedsDamage,
	CPED_CONFIG_FLAG_AllowContinuousThreatResponseWantedLevelUpdates,
	CPED_CONFIG_FLAG_KeepTargetLossResponseOnCleanup,
	CPED_CONFIG_FLAG_PlayersDontDragMeOutOfCar,
	CPED_CONFIG_FLAG_BroadcastRepondedToThreatWhenGoingToPointShooting,
	CPED_CONFIG_FLAG_IgnorePedTypeForIsFriendlyWith,
	CPED_CONFIG_FLAG_TreatNonFriendlyAsHateWhenInCombat,
	CPED_CONFIG_FLAG_DontLeaveVehicleIfLeaderNotInVehicle,
	CPED_CONFIG_FLAG_ChangeFromPermanentToAmbientPopTypeOnMigration,
	CPED_CONFIG_FLAG_AllowMeleeReactionIfMeleeProofIsOn,
	CPED_CONFIG_FLAG_UsingLowriderLeans,
	CPED_CONFIG_FLAG_UsingAlternateLowriderLeans,
	CPED_CONFIG_FLAG_UseNormalExplosionDamageWhenBlownUpInVehicle,
	CPED_CONFIG_FLAG_DisableHomingMissileLockForVehiclePedInside,
	CPED_CONFIG_FLAG_DisableTakeOffScubaGear,
	CPED_CONFIG_FLAG_IgnoreMeleeFistWeaponDamageMult,
	CPED_CONFIG_FLAG_LawPedsCanFleeFromNonWantedPlayer,
	CPED_CONFIG_FLAG_ForceBlipSecurityPedsIfPlayerIsWanted,
	CPED_CONFIG_FLAG_IsHolsteringWeapon,
	CPED_CONFIG_FLAG_UseGoToPointForScenarioNavigation,
	CPED_CONFIG_FLAG_DontClearLocalPassengersWantedLevel,
	CPED_CONFIG_FLAG_BlockAutoSwapOnWeaponPickups,
	CPED_CONFIG_FLAG_ThisPedIsATargetPriorityForAI,
	CPED_CONFIG_FLAG_IsSwitchingHelmetVisor,
	CPED_CONFIG_FLAG_ForceHelmetVisorSwitch,
	CPED_CONFIG_FLAG_IsPerformingVehicleMelee,
	CPED_CONFIG_FLAG_UseOverrideFootstepPtFx,
	CPED_CONFIG_FLAG_DisableVehicleCombat,
	CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamage,
	CPED_CONFIG_FLAG_AllowBikeAlternateAnimations,
	CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamageNonSynced,
	CPED_CONFIG_FLAG_UseLockpickVehicleEntryAnimations,
	CPED_CONFIG_FLAG_IgnoreInteriorCheckForSprinting,
	CPED_CONFIG_FLAG_SwatHeliSpawnWithinLastSpottedLocation,
	CPED_CONFIG_FLAG_DisableStartEngine,
	CPED_CONFIG_FLAG_IgnoreBeingOnFire,
	CPED_CONFIG_FLAG_DisableTurretOrRearSeatPreference,
	CPED_CONFIG_FLAG_DisableWantedHelicopterSpawning,
	CPED_CONFIG_FLAG_UseTargetPerceptionForCreatingAimedAtEvents,
	CPED_CONFIG_FLAG_DisableHomingMissileLockon,
	CPED_CONFIG_FLAG_ForceIgnoreMaxMeleeActiveSupportCombatants,
	CPED_CONFIG_FLAG_StayInDefensiveAreaWhenInVehicle,
	CPED_CONFIG_FLAG_DontShoutTargetPosition,
	CPED_CONFIG_FLAG_DisableHelmetArmor,
	CPED_CONFIG_FLAG_CreatedByConcealedPlayer,
	CPED_CONFIG_FLAG_PermanentlyDisablePotentialToBeWalkedIntoResponse,
	CPED_CONFIG_FLAG_PreventVehExitDueToInvalidWeapon,
	CPED_CONFIG_FLAG_IgnoreNetSessionFriendlyFireCheckForAllowDamage,
	CPED_CONFIG_FLAG_DontLeaveCombatIfTargetPlayerIsAttackedByPolice,
	CPED_CONFIG_FLAG_CheckLockedBeforeWarp,
	CPED_CONFIG_FLAG_DontShuffleInVehicleToMakeRoom,
	CPED_CONFIG_FLAG_GiveWeaponOnGetup,
	CPED_CONFIG_FLAG_DontHitVehicleWithProjectiles,
	CPED_CONFIG_FLAG_DisableForcedEntryForOpenVehiclesFromTryLockedDoor,
	CPED_CONFIG_FLAG_FiresDummyRockets,
	CPED_CONFIG_FLAG_PedIsArresting,
	CPED_CONFIG_FLAG_IsDecoyPed,
	CPED_CONFIG_FLAG_HasEstablishedDecoy,
	CPED_CONFIG_FLAG_BlockDispatchedHelicoptersFromLanding,
	CPED_CONFIG_FLAG_DontCryForHelpOnStun,
	CPED_CONFIG_FLAG_HitByTranqWeapon,
	CPED_CONFIG_FLAG_CanBeIncapacitated,
	CPED_CONFIG_FLAG_ForcedAimFromArrest,
	CPED_CONFIG_FLAG_CanFlyThruWindscreen = 32,
	CPED_CONFIG_FLAG_SuperDead = 73,
	CPED_CONFIG_FLAG_IsOnGround = 60,
	CPED_CONFIG_FLAG_NoCollision = 52,
};
using ePedConfigFlag = ePedConfigFlags;
#pragma endregion
class CPed;
class CVehicle;
class CPlayerInfo;
class CWeaponManager;
#pragma region Infos
class CPlayerInfo {
public:
int PlayerID( ) {
if ( !this ) { return 0; }
return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_PlayerId );
}
void SetInfStamina( bool Toggle ) {
if ( !this ) { return; }
Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + 0xCF4, Toggle ? FLT_MAX : 100 );
}
};
class CWeaponInfo {
public:
std::string GetName( ) {
if ( !this ) { return xorstr( "" ); }
return Mem.ReadString( Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x5F0 ) );
}
};
#pragma endregion
#pragma region List
class CVehicleList {
public:
CVehicle * Vehicle( int Idx )
{
if ( !this ) { return 0; }
return ( CVehicle * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + ( Idx * 0x10U ) );
}
};
class CPedList {
public:
CPed * Ped( int Idx ) {
if ( !this ) { return 0; }
return ( CPed * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + ( Idx * 0x10U ) );
}
};
#pragma endregion
#pragma region InterFaces
class CPedInterFace {
public:
int MaxPed( ) { return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + 0x108 ); }
int PedCount( ) { return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + 0x110 ); }
CPedList * PedList( ) { return ( CPedList * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x100 ); }
};
class CVehInterFace {
public:
int MaxVehicles( ) { return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + 0x188 ); }
int VehicleCount( ) { return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + 0x190 ); }
CVehicleList * VehicleList( ) { return ( CVehicleList * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x180 ); }
};
class CReplayInterFace {
public:
CPedInterFace * InterfacePed( ) {
if ( !this ) { return 0; }
return ( CPedInterFace * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x18 );
}
CVehInterFace * InterfaceVeh( ) {
if ( !this ) { return 0; }
return ( CVehInterFace * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x10 );
}
};
#pragma endregion
class CPed {
public:
float GetMaxHealth( ) {
if ( !this ) { return 0; }
return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_MaxHealth );
}
float GetHealth( ) {
if ( !this ) { return 0; }
return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + 0x280 );
}
void SetHealth( float Health ) {
if ( !this ) { return; }
Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + 0x280, Health );
}
float GetArmor( ) {
if ( !this ) { return 0; }
return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_Armor );
}
void SetArmor( float Armor ) {
if ( !this ) { return; }
Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_Armor, Armor );
}
float GetSpeed( ) {
if ( !this ) { return 0; }
CPlayerInfo * PlayerInfo = this->GetPlayerInfo( );
return Mem.Read<float>( reinterpret_cast< uintptr_t >( PlayerInfo ) + g_Offsets.m_Speed );
}
void SetSpeed( float Speed ) {
if ( !this ) { return; }
CPlayerInfo * PlayerInfo = this->GetPlayerInfo( );
Mem.Write<float>( reinterpret_cast< uintptr_t >( PlayerInfo ) + g_Offsets.m_Speed, Speed );
}
D3DXVECTOR3 GetPos( ) {
if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
return Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90 );
}
void SetPos( D3DXVECTOR3 Pos ) {
if ( !this ) { return; }
bool InsideVehicle = InVehicle( );
uintptr_t LastVeh = reinterpret_cast< uintptr_t >( GetLastVehicle( ) );
if ( LastVeh && InsideVehicle ) {
uintptr_t Navigation = Mem.Read<uintptr_t>( LastVeh + 0x30 );
Mem.Write<D3DXVECTOR3>( Navigation + 0x30, D3DXVECTOR3( 0, 0, 0 ) );
Mem.Write<D3DXVECTOR3>( LastVeh + 0x90, Pos );
}
else if ( !InsideVehicle ) {
uintptr_t Navigation = this->GetNavigation( );
Mem.Write<D3DXVECTOR3>( Navigation + 0x30, D3DXVECTOR3 { 0, 0, 0 } );
Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90, Pos );
}
}
void SeatBealt(bool toggle) {
if (!this) { return; }
bool InsideVehicle = InVehicle();
if (InsideVehicle) {
if (toggle) {
uintptr_t Path = Mem.FindSignature({ 0x83, 0xa1, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x83, 0xe2 });
Mem.WriteBytes(Path, { 0x90,0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, });
Mem.Write<BYTE>((uintptr_t)this + g_Offsets.m_SeatBealt, 0xC9);
}
else {
Mem.Write<BYTE>((uintptr_t)this + g_Offsets.m_SeatBealt, 0xC8);
}
}
}
CVehicle* GetLastVehicle() {
if (!this) return 0;
return (CVehicle*)Mem.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + g_Offsets.m_LastVehicle);
}
CPlayerInfo * GetPlayerInfo( ) {
if ( !this ) return 0;
return ( CPlayerInfo * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_PlayerInfo );
}
CWeaponManager * GetWeaponManager( ) {
if ( !this ) return 0;
return ( CWeaponManager * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_WeaponManager );
}
uint32_t GetPedType( ) {
if ( !this ) { return 0; }
return Mem.Read<uint32_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_EntityType ) << 11 >> 25;
}
int GetID( ) {
if ( !this ) { return 0; }
CPlayerInfo * PlayerInfo = ( CPlayerInfo * ) GetPlayerInfo( );
int Id = PlayerInfo->PlayerID( );
return Id;
}
bool HasFlag( ePedConfigFlag Flag )
{
if ( !this ) { return false; }
auto v1 = ( int ) Flag;
if ( !this || v1 > 0x1CA ) return false;
auto v2 = 1 << ( v1 & 0x1F );
auto v3 = v1 >> 5;
auto v4 = reinterpret_cast< uintptr_t >( this ) + 4 * v3 + g_Offsets.m_PedFlag;
auto v5 = Mem.Read<long>( v4 );
return ( v2 & v5 ) != 0;
}
void SetConfigFlag( ePedConfigFlag Flag, bool Value )
{
if ( !this ) { return; }
auto v1 = ( int ) Flag;
if ( !this || v1 > 0x1CA ) return;
auto v2 = 1 << ( v1 & 0x1F );
auto v3 = v1 >> 5;
auto v4 = ( uintptr_t ) ( this ) + 4 * v3 + g_Offsets.m_PedFlag;
auto v5 = Mem.Read<long>( v4 );
if ( Value != ( ( v2 & v5 ) != 0 ) ) {
auto v6 = v2 & ( v5 ^ -( uint8_t ) ( Value ? 1 : 0 ) );
v5 ^= v6;
Mem.Write( v4, v5 );
}
}
bool IsVisible( ) {
if ( !this ) return false;
return HasFlag( ePedConfigFlag::CPED_CONFIG_FLAG_VisibleOnScreen );
}
float GetLastVisibleTime( ) {
if ( !this ) return 0.0f;
return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_LastVisibleTime );
}
bool InVehicle( ) {
if ( !this ) return false;
return HasFlag( ePedConfigFlag::CPED_CONFIG_FLAG_InVehicle );
}
void NoRagDoll( bool Toggle )
{
if ( !this ) return;
Mem.Write<BYTE>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_NoRagDoll, Toggle ? 0x80 : 0x20 );
}
void Invisible( bool Toggle )
	{
		if ( !this ) return;
		uint8_t value = Toggle ? 0x1 : 0x37;
		Mem.Write<uint8_t>( reinterpret_cast< uintptr_t >( this ) + 0x189, value );
	}
	uint64_t GetNetObject() {
		if (!this) return 0;
		return Mem.Read<uint64_t>(reinterpret_cast<uintptr_t>(this) + 0xD0);
	}
	void SetNetObjectInvisible(bool enable) {
		uint64_t netObject = GetNetObject();
		if (!netObject) return;
		// 0xD1 é o offset do flag de invisibilidade no net object 
		Mem.Write<uint8_t>(netObject + 0xD1, enable ? 1 : 0);
	}
void Invisible_ON( )
{
if ( !this ) return;
Mem.Write<uint8_t>( reinterpret_cast< uintptr_t >( this ) + 0xAC, 0 );
}
void Invisible_Off( )
{
if ( !this ) return;
Mem.Write<uint8_t>( reinterpret_cast< uintptr_t >( this ) + 0xAC, 1 );
}
D3DXVECTOR3 GetVelocity( ) {
if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
return Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x320 );
}
void FreezePed( bool Toggle ) {
if ( !this ) { return; }
if ( !InVehicle( ) ) {
uintptr_t CModelInfo = Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x20 );
Mem.Write<float>( CModelInfo + 0x2C, Toggle ? 0.f : 1.f );
}
else {
Mem.Write<BYTE>( reinterpret_cast< uintptr_t >( GetLastVehicle( ) ) + 0x2E, Toggle ? 1 : 2 );
}
}
void SetGodMode( bool Toggle ) {
if ( !this ) { return; }
uintptr_t Addr = reinterpret_cast< uintptr_t >( this ) + 0x188;
Mem.Write<DWORD>( Addr, Toggle ? 0x1000U : 0x0000U );
}
void SetInfStamina( bool Toggle ) {
if ( !this ) { return; }
CPlayerInfo * PlayerInfo = ( CPlayerInfo * ) GetPlayerInfo( );
Mem.Write<float>( reinterpret_cast< uintptr_t >( PlayerInfo ) + 0xCF4, Toggle ? FLT_MAX : 100 );
}
void SetInfCombatRoll( bool enable ) {
if ( !this ) { return; }
uintptr_t Address = g_Offsets.m_InfiniteCombatRoll;
static std::vector<uint8_t> OriginalTable;
if ( OriginalTable.empty( ) ) {
OriginalTable = Mem.ReadBytes( Address, 6 );
}
std::vector <uint8_t> Patch = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
Mem.WriteBytes( Address, enable ? Patch : OriginalTable );
}
D3DXVECTOR3 GetBonePosDefault( const int Bone )
{
if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
D3DXMATRIX Mtx = Mem.Read<D3DXMATRIX>( reinterpret_cast< uintptr_t >( this ) + 0x60 );
D3DXVECTOR3 BonePos = Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + ( g_Offsets.CurrentBuild >= 2802 ? 0x410 : 0x430 + Bone * 0x10 ) );;
D3DXVECTOR4 Transform;
D3DXVec3Transform( &Transform, &BonePos, &Mtx );
return D3DXVECTOR3( Transform.x, Transform.y, Transform.z );
}
float GetDistance( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2 ) {
return std::sqrtf( std::pow( pos2.x - pos1.x, 2.f ) + std::pow( pos2.y - pos1.y, 2.f ) );
}
uintptr_t GetCPedInventory( ) {
if ( !this ) { return 0; }
return Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + ( g_Offsets.m_WeaponManager - 8 ) );
}
uintptr_t GetNavigation( ) {
if ( !this ) { return 0; }
return Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x30 );
}
void RemoveKinematics( )
{
if ( !g_Offsets.m_ArmsKinematics || !g_Offsets.m_LegsKinematics )
return;
Mem.PatchFunc( g_Offsets.m_ArmsKinematics, 5 );
Mem.PatchFunc( g_Offsets.m_LegsKinematics, 5 );
}
void ForceWeaponWheel( bool toggle )
{
if ( !this ) return;
static uintptr_t DisableControlAction = 0;
static uintptr_t HideHudComponentThisFrame = 0;
if ( DisableControlAction == 0 ) {
DisableControlAction = Mem.FindSignature(
{ 0x48, 0x8b, 0x41, 0x00 , 0x83, 0x78, 0x00 , 0x00 , 0x8b, 0x50, 0x00 , 0x8b, 0x08, 0xe9, 0x00 , 0x00 , 0x00 , 0x00 , 0x48, 0x89, 0x5c, 0x24 }
);
}
if ( HideHudComponentThisFrame == 0 ) {
HideHudComponentThisFrame = Mem.FindSignature(
{ 0x48, 0x83, 0xec, 0x00 , 0x48, 0x8b, 0x41, 0x00 , 0x83, 0x38, 0x00 , 0x48, 0x89, 0x6c, 0x24 }
);
}
if ( toggle ) {
Mem.WriteBytes( DisableControlAction, { 0xC3 } );
Mem.WriteBytes( HideHudComponentThisFrame, { 0xC3 } );
SetConfigFlag( CPED_CONFIG_FLAG_BlockWeaponSwitching, false );
}
else {
Mem.WriteBytes( DisableControlAction, { 0x48 } );
Mem.WriteBytes( HideHudComponentThisFrame, { 0x48 } );
SetConfigFlag( CPED_CONFIG_FLAG_BlockWeaponSwitching, true );
}
}
};
class CHandlingData {
public:
uint64_t qword0;
uint32_t m_model_hash;
float m_mass;
float m_initial_drag_coeff;
float m_downforce_multiplier;
float m_popup_light_rotation;
char pad_001C[ 4 ];
D3DXVECTOR3 m_centre_of_mass;
char pad_002C[ 4 ];
D3DXVECTOR3 m_inertia_mult;
char pad_003C[ 4 ];
float m_buoyancy;
float m_drive_bias_rear;
float m_drive_bias_front;
float m_acceleration;
uint8_t m_initial_drive_gears;
char pad_0051[ 3 ];
float m_drive_inertia;
float m_upshift;
float m_downshift;
float m_initial_drive_force;
float m_drive_max_flat_velocity;
float m_initial_drive_max_flat_vel;
float m_brake_force;
char pad_0070[ 4 ];
float m_brake_bias_front;
float m_brake_bias_rear;
float m_handbrake_force;
float m_steering_lock;
float m_steering_lock_ratio;
float m_traction_curve_max;
float m_traction_curve_lateral;
float m_traction_curve_min;
float m_traction_curve_ratio;
float m_curve_lateral;
float m_curve_lateral_ratio;
float m_traction_spring_delta_max;
float m_traction_spring_delta_max_ratio;
float m_low_speed_traction_loss_mult;
float m_camber_stiffness;
float m_traction_bias_front;
float m_traction_bias_rear;
float m_traction_loss_mult;
float m_suspension_force;
float m_suspension_comp_damp;
float m_suspension_rebound_damp;
float m_suspension_upper_limit;
float m_suspension_lower_limit;
float m_suspension_raise;
float m_suspension_bias_front;
float m_suspension_bias_rear;
float m_anti_rollbar_force;
float m_anti_rollbar_bias_front;
float m_anti_rollbar_bias_rear;
float m_roll_centre_height_front;
float m_roll_centre_height_rear;
float m_collision_damage_mult;
float m_weapon_damamge_mult;
float m_deformation_mult;
float m_engine_damage_mult;
float m_petrol_tank_volume;
float m_oil_volume;
char pad_0108[ 4 ];
D3DXVECTOR3 m_seat_offset_dist;
uint32_t m_monetary_value;
char pad_011C[ 8 ];
uint32_t m_model_flags;
uint32_t m_handling_flags;
uint32_t m_damage_flags;
char pad_0130[ 12 ];
uint32_t m_ai_handling_hash;
char pad_140[ 24 ];
};
class CVehicle {
public:
D3DXVECTOR3 GetPos( ) {
if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
return Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90 );
}
void SetPos( D3DXVECTOR3 Pos ) {
if ( !this ) { return; }
Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90, Pos );
}
uintptr_t GetHandling( ) {
if ( !this ) { return 0; }
return Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_Handling );
}
uint64_t GetModelInfo()
{
if (!this)
return 0;
return Mem.Read<uint64_t>(reinterpret_cast<uint64_t>(this) + 0x20);
}
void SetExtras(uint32_t value) {
Mem.Write<uint32_t>((uintptr_t)this + g_Offsets.m_VehicleExtras, value);
}
void  GetGodMode(bool Toggle) {
if (!this) { return; }
uintptr_t Addr = reinterpret_cast<uintptr_t>(this) + 0x188;
DWORD flag = Mem.Read<DWORD>(Addr);
Mem.Write<DWORD>(Addr, Toggle == true ? 0x1000U : 0x0000U);
}
void SetGodMode(bool Toggle) {
if (!this) { return; }
uintptr_t Addr = reinterpret_cast<uintptr_t>(this) + 0x188;
DWORD flag = Mem.Read<DWORD>(Addr);
Mem.Write<DWORD>(Addr, Toggle == true ? 0x1000U : 0x0000U);
}
float GetGravity( ) {
if ( !this ) { return 0; }
return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleGravity );
}
void Fix( ) {
if ( !this ) { return; }
float Value = 1000.0f;
Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + 0x970, Value );
uintptr_t vehNav = Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x30 );
if ( vehNav ) {
const float PI = 3.14159265358979323846f;
float currentRoll = Mem.Read<float>( vehNav + 0x28 );
float newRoll = currentRoll + PI;
if ( newRoll > PI ) newRoll -= 2 * PI;
if ( newRoll < -PI ) newRoll += 2 * PI;
Mem.Write<float>( vehNav + 0x28, newRoll );
Mem.Write<float>( vehNav + 0x24, 0.0f );
D3DXVECTOR3 currentPos = Mem.Read<D3DXVECTOR3>( vehNav + 0x50 );
currentPos.z += 2.0f;
Mem.Write<D3DXVECTOR3>( vehNav + 0x50, currentPos );
Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90, currentPos );
Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x320, D3DXVECTOR3( 0.0f, 0.0f, 5.0f ) );
}
}
void SetGravity( float Value ) {
if ( !this ) { return; }
Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleGravity, Value );
}
bool IsLocked( ) {
if ( !this ) { return false; }
return Mem.Read<uint32_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleDoorsLockState ) == 2;
}
void DoorState( bool Unlock ) {
if ( !this ) { return; }
Mem.Write<uint32_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleDoorsLockState, Unlock ? 1 : 2 );
}
D3DXVECTOR3 GetVelocity( ) {
if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
return Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x320 );
}
CPed * GetDriver( )
{
if ( !this ) return 0;
return ( CPed * )Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleDriver );
}
};
class CWeaponManager {
public:
CWeaponInfo * GetWeaponInfo( ) {
if ( !this ) { return 0; }
return ( CWeaponInfo * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x20 );
}
float GetRecoil( ) {
if ( !this ) { return 0.0f; }
CWeaponInfo * WeaponInfo = ( CWeaponInfo * ) GetWeaponInfo( );
return Mem.Read<float>( ( uintptr_t ) WeaponInfo + g_Offsets.m_Recoil );
}
float SetRecoil( float Recoil ) {
if ( !this ) { return 0.0f; }
CWeaponInfo * WeaponInfo = ( CWeaponInfo * ) GetWeaponInfo( );
return Mem.Write<float>( ( uintptr_t ) WeaponInfo + g_Offsets.m_Recoil, Recoil );
}
float GetSpread( ) {
if ( !this ) { return 0.0f; }
CWeaponInfo * WeaponInfo = ( CWeaponInfo * ) GetWeaponInfo( );
return Mem.Read<float>( ( uintptr_t ) WeaponInfo + g_Offsets.m_Spread );
}
float SetSpread( float Spread ) {
if ( !this ) { return 0.0f; }
CWeaponInfo * WeaponInfo = ( CWeaponInfo * ) GetWeaponInfo( );
return Mem.Write<float>( ( uintptr_t ) WeaponInfo + g_Offsets.m_Spread, Spread );
}
};
class CPedFactory {
public:
CPed * GetLocalPlayer( ) {
if ( !this ) { return 0; }
return ( CPed * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x8 );
}
};
