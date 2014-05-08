/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import "IStoreAssets.h"

@class MarketItem;
@class PurchasableVirtualItem;
@class SoomlaVerification;

/**
 * This class holds the most basic assets needed to operate the Store.
 * You can use it to purchase products from the App Store.
 *
 * This is the only class you need to initialize in order to use the SOOMLA SDK.
 *
 * In addition to initializing this class, you'll also have to call
 * StoreController::storeOpening and StoreController::storeClosing when you open the store window or close it. These two
 * calls initializes important components that support billing and storage information (see implementation below).
 *
 */
@interface StoreController : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>{
    @private
    BOOL initialized;
    SoomlaVerification* sv;
}

@property BOOL initialized;

+ (StoreController*)getInstance;

/**
 * Initializes StoreController from your implementation of IStoreAssets. This initializer also initializes StoreInfo.
 *
 * storeAssets - the definition of your application specific assets.
 * customSecret - your encryption secret (it's used to encrypt your data in the database).
 * return: true if successful
 */
- (BOOL)initializeWithStoreAssets:(id<IStoreAssets>)storeAssets andCustomSecret:(NSString*)secret;

/**
 * Starts an in app purchase process in the App Store.
 * 
 * marketItem - the item to purchase. This item has to be defined EXACTLY the same in iTunes Connect.
 * return: true if successful
 */
- (BOOL)buyInMarketWithMarketItem:(MarketItem*)marketItem;

/**
 * Initiates the restoreTransactions process and will refresh all purchasable items' details from the App Store.
 */
- (void)refreshInventory;

/**
 * Initiates the restoreTransactions process.
 */
- (void)restoreTransactions;

/**
 * Checks if transactions were already restored.
 *
 * return: true if transactions were restored, false otherwise.
 */
- (BOOL)transactionsAlreadyRestored;

/**
 * Refreshes the details of all market-purchasable items that were defined in App Store.
 * This function will invoke the event EVENT_ITEMS_MARKET_REFRESHED when finished.
 */
- (void)refreshMarketItemsDetails;

/**
 * Checks if StoreController has already been initialized.
 *
 * return: true if initialized, false otherwise.
 */
- (BOOL)isInitialized;
@end
